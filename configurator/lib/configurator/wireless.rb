module Configurator
  module Wireless
    extend System

    module_function

    def enable_managed_mode(interface)
      execute("wpa_action #{interface} stop")
      execute('service isc-dhcp-server stop')
      execute("ip addr flush dev #{interface}")
      execute("ifup #{interface}")

      # If the wired interface is connected, disconnect the wireless connection
      execute("wpa_cli -i #{interface} disconnect") if Wired.link_beat?

      true
    end

    def enable_adhoc_mode(interface, ip, ssid)
      execute("wpa_action #{interface} stop")
      execute("ip link set #{interface} up")
      execute("iwconfig #{interface} mode ad-hoc")
      execute("iwconfig #{interface} essid #{ssid}")
      execute("ip addr add #{ip} brd + dev #{interface}")
      execute('service isc-dhcp-server start')
      true
    end

  end
end
