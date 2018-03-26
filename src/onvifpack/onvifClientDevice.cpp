#include <onvifClientDevice.h>
#include <wsseapi.h>


OnvifClientDevice::OnvifClientDevice(const std::string & ipv4_address,
                                     const std::string & username,
                                     const std::string & password) {
	_ocp_soap_endpoint = "http://" + ipv4_address + "/onvif/device_service";
	_ocp_username = username;
	_ocp_password = password;
	_ocp_ipv4_address = ipv4_address;
	proxyDevice.soap_endpoint = _ocp_soap_endpoint.c_str();
	soap_register_plugin(proxyDevice.soap, soap_wsse);
}

bool OnvifClientDevice::GetCapabilities(CapabilitiesURI & capabilitiesURI) {

	struct soap* soap = soap_new();

	_tds__GetCapabilities* tds__GetCapabilities = soap_new__tds__GetCapabilities(soap);
	tds__GetCapabilities->Category.push_back(tt__CapabilityCategory__All);

	_tds__GetCapabilitiesResponse* tds__GetCapabilitiesResponse = soap_new__tds__GetCapabilitiesResponse(soap);

	bool execute_result = true;

	if (SOAP_OK == proxyDevice.GetCapabilities(tds__GetCapabilities, tds__GetCapabilitiesResponse)) {
		if (tds__GetCapabilitiesResponse->Capabilities->Analytics != NULL) {
			capabilitiesURI.analyticsXAddr =  tds__GetCapabilitiesResponse->Capabilities->Analytics->XAddr;
		}
		if (tds__GetCapabilitiesResponse->Capabilities->Device != NULL) {
			capabilitiesURI.deviceXAddr = tds__GetCapabilitiesResponse->Capabilities->Device->XAddr;
		}
		if (tds__GetCapabilitiesResponse->Capabilities->Events != NULL) {
			capabilitiesURI.eventsXAddr = tds__GetCapabilitiesResponse->Capabilities->Events->XAddr;
		}
		if (tds__GetCapabilitiesResponse->Capabilities->Imaging != NULL) {
			capabilitiesURI.imagingXAddr = tds__GetCapabilitiesResponse->Capabilities->Imaging->XAddr;
		}
		if (tds__GetCapabilitiesResponse->Capabilities->Media != NULL) {
			capabilitiesURI.mediaXAddr = tds__GetCapabilitiesResponse->Capabilities->Media->XAddr;
		}
		if (tds__GetCapabilitiesResponse->Capabilities->PTZ != NULL) {
			capabilitiesURI.ptzXAddr = tds__GetCapabilitiesResponse->Capabilities->PTZ->XAddr;
		}

		execute_result = true;
	} else {
		//		PrintErr(proxyDevice.soap);
		execute_result = false;
	}

	soap_destroy(soap);
	soap_end(soap);

	return execute_result;
}
