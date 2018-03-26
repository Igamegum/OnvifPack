#ifndef ONVIF_CLIENT_REMOTEDISCOVERY_H_
#define ONVIF_CLIENT_REMOTEDISCOVERY_H_

#include <vector>
#include <string>


typedef struct {
	std::string UUID;
	std::vector<std::string> WsddUris; 
	std::string IPv4;
}_ocp__Device;

std::vector<std::string> CycleSplit(const std::string &,const char &);


class OnvifClientRemoteDiscovery {
	public:
		/*devices,timeout,network_card_address*/
        bool ProbeMatch(std::vector<_ocp__Device> &,
                        const int & recv_timeout = 3,
                        const std::string & netword_card_address = "") ;
};


#endif
