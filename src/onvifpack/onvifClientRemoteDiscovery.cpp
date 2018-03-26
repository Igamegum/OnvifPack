#include <onvifClientRemoteDiscovery.h>
#include <soapPullPointSubscriptionBindingProxy.h>
#include <soapRemoteDiscoveryBindingProxy.h>
#include <map>
#include <sstream>
#include <wsaapi.h>
#include <regex>
#include <ifaddrs.h>

std::vector<std::string> CycleSplit(const std::string & src,const char &delim) {
	std::stringstream ss(src);
	std::string item;
	std::vector<std::string> elems;
	while (std::getline(ss, item, delim)) {
		elems.push_back(std::move(item));
	}
	return elems;
}

bool OnvifClientRemoteDiscovery::ProbeMatch(std::vector<_ocp__Device> & devices,
                                            const int & recv_timeout,
                                            const std::string & netword_card_address) {

	 const std::string was_To = "urn:schemas-xmlsoap-org:ws:2005:04:discovery";  
	 const std::string was_Action = "http://schemas.xmlsoap.org/ws/2005/04/discovery/Probe";  
	 const std::string soap_endpoint = "soap.udp://239.255.255.250:3702"; 
	 const std::string soap_empty = "";

	 struct soap * soap = soap_new();

	 SOAP_ENV__Header header;
	 soap_default_SOAP_ENV__Header(soap,&header);

	 /* if the netword_card_address is empty ,use default ipaddress */
	 if (netword_card_address.length() > 0) {
		 struct in_addr if_req;
		 if_req.s_addr = inet_addr(netword_card_address.c_str());

		 if (if_req.s_addr == INADDR_NONE) {
			 soap_destroy(soap);
			 soap_end(soap);
			 soap_done(soap);
			 return false;
		 }
		 soap->ipv4_multicast_if = (char*)soap_malloc(soap, sizeof(in_addr));
		 memset(soap->ipv4_multicast_if, 0, sizeof(in_addr));
		 memcpy(soap->ipv4_multicast_if, (char*)&if_req, sizeof(if_req));
	 }


	 header.wsa__MessageID = const_cast<char *>(soap_wsa_rand_uuid(soap));
	 header.wsa__To        = const_cast<char *>(was_To.c_str());
	 header.wsa__Action    = const_cast<char *>(was_Action.c_str());

	 soap->header = &header;
	 soap->recv_timeout = recv_timeout;

	 soap_set_namespaces(soap,namespaces);
	 
	 wsdd__ScopesType scopesType;
	 soap_default_wsdd__ScopesType(soap,&scopesType);
	 scopesType.__item = const_cast<char *>(soap_empty.c_str());

	 wsdd__ProbeType probeType;
	 soap_default_wsdd__ProbeType(soap,&probeType);
	 probeType.Scopes = &scopesType;
	 probeType.Types = const_cast<char *>(soap_empty.c_str());

	 std::map<std::string,_ocp__Device> devices_map;

	 bool execute_result = true;

	 if (SOAP_OK == soap_send___wsdd__Probe(soap,soap_endpoint.c_str(),nullptr,&probeType)) {

		 struct __wsdd__ProbeMatches resp;
		 while (SOAP_OK == soap_recv___wsdd__ProbeMatches(soap,&resp)) {

			 if (resp.wsdd__ProbeMatches->ProbeMatch) {

				 _ocp__Device device;

				 if (resp.wsdd__ProbeMatches->ProbeMatch->wsa__EndpointReference.Address == nullptr) {
					 continue;
				 }
				 //extract the uuid
				 const std::string _ocp_uuid = std::string(resp.wsdd__ProbeMatches->ProbeMatch->wsa__EndpointReference.Address);
				 device.UUID = _ocp_uuid;

				 if (resp.wsdd__ProbeMatches->ProbeMatch->XAddrs) {
					  device.WsddUris = CycleSplit(resp.wsdd__ProbeMatches->ProbeMatch->XAddrs, ' ');
				 }

				 //extract the ipv4 address
				 if (device.WsddUris.size() > 0) {
					 bool finder = false;
					 for (int i = 0; i < device.WsddUris.size(); ++i) {
						 const std::string  pattern = "([0-9]{1,3}[.]){3}[0-9]{1,3}";
						 std::regex _regex(pattern);
						 std::smatch sm;
						 while (std::regex_search(device.WsddUris[i],sm,_regex)) {
							 if (sm.size() > 0) {
								 device.IPv4 = sm[0];
								 finder = true;
								 break;
							 }
						 }
						 if (finder) {
							 break;
						 }
					 }
				 }

				 if (devices_map.find(device.UUID) == devices_map.end()) {
					 devices_map[device.UUID] = device;
				 }
			 }

		 }

		 devices.clear();


		 for (auto iter : devices_map) {
			 devices.emplace_back(std::move(iter.second));
		 }

	 } else {
		 execute_result = false;
	 }

	soap_destroy(soap); 
	soap_end(soap);
	soap_done(soap);


	return execute_result;
}
