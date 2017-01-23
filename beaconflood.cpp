
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <tins/tins.h>

using namespace Tins;

RadioTap new_rt_dot11beacon(const Dot11::address_type& bssid, const std::string& essid)
{
Dot11Beacon beacon;
beacon.addr2(bssid);
beacon.addr3(bssid);
beacon.ssid(essid);
beacon.ds_parameter_set(8);
beacon.supported_rates({1.0f, 5.5f, 11.0f});
beacon.rsn_information(RSNInformation::wpa2_psk());
return RadioTap() / beacon;
}

int main (int argc, char **argv)
{
NetworkInterface iface(argc > 1 ? argv[1] : "wlx909f3308a0fc");
PacketSender sender;
RadioTap outer1(new_rt_dot11beacon("c2:11:08:ed:80:00", "1.길길짱잘생김")),
outer2(new_rt_dot11beacon("d2:11:08:ed:80:00", "2.길길정말잘생김")),
outer3(new_rt_dot11beacon("e2:11:08:ed:80:00", "3.길길너무잘생김"));
while (1)
{
sender.send(outer1, iface);
sender.send(outer2, iface);
sender.send(outer3, iface);
usleep(1);
}
}
