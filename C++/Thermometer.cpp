/* 
 * File:   Thermometer.cpp
 * Author: Richard Greene
 * 
 * Measures and reports temperature.
 * 
 * Created on October 22, 2014, 12:58 PM
 */
#include <iostream>
#include <glob.h>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <stdexcept>

#include <Thermometer.h>
#include <Settings.h>
#include <Logger.h>
#include <Filenames.h>

/// The only public constructor.  'haveHardware' can only be false in debug
/// builds, for test purposes only.  Gets the name of the file that holds 
/// temperature measurements.
Thermometer::Thermometer(bool haveHardware) :
_temperature(-1.0),
_getTemperatureThread(0)
{
#ifndef DEBUG
    if(!haveHardware)
    {
        LOGGER.LogError(LOG_ERR, errno, ERR_MSG(HardwareNeeded));
        exit(-1);
    }
#endif  

    glob_t gl;

    // enumerate temperature sensor via 1-wire file system 
    if(glob(THERMOMETER_FILE, GLOB_NOSORT, NULL, &gl) == 0)
    {
        _temperatureFile = gl.gl_pathv[0];
    }
    else
    {
        if(SETTINGS.GetInt(HARDWARE_REV) != 0 && haveHardware)
            throw std::runtime_error(ErrorMessage::Format(CantOpenThermometer, errno));
        
        _temperatureFile.clear();
    }
    
    globfree(&gl);    
}

/// Measure the current temperature and store it for future reference.  
double Thermometer::GetTemperature()
{
    if(_temperatureFile.empty())
        return -1.0;
    
    // make sure a temperature reading thread isn't already running
    AwaitThreadComplete();

    // initiate temperature reading (that can take up to 1.5 s)
    // in a separate thread, to avoid blocking here
    pthread_create(&_getTemperatureThread, NULL, &ThreadHelper, this);  
        
    // return the most recent temperature reading
    return _temperature;
}

/// Wait for any temperature reading in progress to finish.
void Thermometer::AwaitThreadComplete()
{
    if(_getTemperatureThread != 0)
    {
        void *result;
        pthread_join(_getTemperatureThread, &result);
    }    
}

/// Thread helper function that reads the thermometer
void* Thermometer::ThreadHelper(void *context)
{
    Thermometer* pThermometer =  (Thermometer*)context; 

    std::string line;
    std::ifstream infile(pThermometer->_temperatureFile.c_str());
    std::getline(infile, line);
    
    // convert to a double
    pThermometer->_temperature = strtod(line.c_str(), NULL);
    pthread_exit(NULL);
}