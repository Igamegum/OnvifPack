#ifndef ONVIF_CLIENT_DEVCE_H_
#define ONVIF_CLIENT_DEVCE_H_

#include <string>
#include <soapDeviceBindingProxy.h>

struct CapabilitiesURI {

	std::string analyticsXAddr;
	std::string deviceXAddr;
	std::string eventsXAddr;
	std::string imagingXAddr;
	std::string mediaXAddr;
	std::string ptzXAddr;
};

class OnvifClientDevice {
	private:
	std::string _ocp_password;
	std::string _ocp_username;
	std::string _ocp_ipv4_address;
	std::string _ocp_soap_endpoint;
	DeviceBindingProxy proxyDevice;
	public:
	OnvifClientDevice(const std::string &,const std::string &,const std::string &) ;
	bool GetCapabilities(CapabilitiesURI &);
};

#endif
