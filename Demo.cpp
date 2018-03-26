#include <stdio.h>
#include <iostream>
#include <map>
#include <sstream>
#include <openssl/rsa.h>
#include <wsdd.nsmap>
#include <wsseapi.h>
#include <wsaapi.h>
#include  <ErrorLog.h>
#include <chrono>
#include <thread>
 
#include <soapDeviceBindingProxy.h>
#include <soapMediaBindingProxy.h>
#include <soapPTZBindingProxy.h>


#include <onvifClientDevice.h>
#include <onvifClientMedia.h>
#include <onvifClientPTZ.h>
#include <onvifClientRemoteDiscovery.h>

#define MAX_HOSTNAME_LEN 128
#define MAX_LOGMSG_LEN 256

const std::string PROFILE_NAME  = "profile_name_252_001";
const std::string PROFILE_TOKEN = "profile_token_252_001";
const std::string PTZ_CONF_TOKEN    = "PTZToken";
const std::string SOURCEVIDEO_CONF_TOKEN = "VideoSourceToken";
const std::string IPV4 = "192.168.0.252";
const std::string USERNAME = "admin";
const std::string PASSWORD = "Thinkjoy";



void OnvifPackageDemo() {

	OnvifClientDevice device(IPV4,USERNAME,PASSWORD);

	CapabilitiesURI url;
	//get capabilities
	{
		if (false == device.GetCapabilities(url)) {
			std::cout << "Execute failed" << std::endl;
		} else {
			std::cout << url.analyticsXAddr << std::endl;
			std::cout << url.ptzXAddr << std::endl;
			std::cout << url.mediaXAddr << std::endl;
			std::cout << url.imagingXAddr << std::endl;
			std::cout << url.eventsXAddr << std::endl;
			std::cout << url.deviceXAddr << std::endl;
		}
		std::cout << std::endl << std::endl;
	}

	OnvifClientMedia media(url.mediaXAddr,USERNAME,PASSWORD);
	//get media profiles
	{
		std::vector<_ocp_Profile> profiles;
		if (true == media.GetProfiles(profiles)) {
			for (int i = 0; i < profiles.size(); ++i) {
				std::cout << profiles[i].profileName << "  " << profiles[i].profileToken << std::endl;
			}
		}
		std::cout << std::endl << std::endl;
	}
	/* //get vider source configurations */
	/* { */
	/* 	std::vector<_ocp_VideoSourceConfigurations> confs; */
	/* 	if (true == media.GetVideoSourceConfigurations(confs)) { */
	/* 		for (int i = 0; i < confs.size(); ++i) { */
	/* 			std::cout << confs[i].token << std::endl; */
	/* 		} */
	/* 	} */
	/* 	std::cout << std::endl << std::endl; */
	/* } */
	/* //get video encoder configurations */
	/* { */
	/* 	std::vector<_ocp_VideoEncoderConfigurations> confs; */
	/* 	if (true == media.GetVideoEncoderConfigurations(confs)) { */
	/* 		for (int i = 0; i < confs.size(); ++i) { */
	/* 			std::cout << confs[i].token << std::endl; */
	/* 		} */
	/* 	} */
	/* 	std::cout << std::endl << std::endl; */
	/* } */

	/* //create media profile */
	/* { */
	/* 	if (true == media.CreateProfile(PROFILE_NAME,PROFILE_TOKEN)) { */
	/* 		std::cout << "Create Profile Successed" << std::endl; */
	/* 	} else { */
	/* 		std::cout << "Create Profile Failed" << std::endl; */
	/* 	} */
	/* 	std::cout << std::endl << std::endl; */
	/* } */

	//add video source configuration
	/* { */
	/* 	if (false == media.AddVideoSourceConfiguration(PROFILE_TOKEN,SOURCEVIDEO_CONF_TOKEN)) { */
	/* 		std::cout << "AddVideoSourceConfiguration failed" << std::endl; */
	/* 	} else { */
	/* 		std::cout << "AddVideoSourceConfiguration successed" << std::endl; */
	/* 	} */
	/* 	std::cout << std::endl << std::endl; */
	/* } */

	//add video encoder configuration
	/* { */
	/* 	if (false == media.AddVideoEncoderConfiguration(PROFILE_TOKEN,ENCODERVIDEO_CONF_TOKEN)) { */
	/* 		std::cout << "AddVideoEncoderConfiguration failed" << std::endl; */
	/* 	} else { */
	/* 		std::cout << "AddVideoEncoderConfiguration successed" << std::endl; */
	/* 	} */
	/* 	std::cout << std::endl << std::endl; */
	/* } */

	//get snapshot uri
	{
		std::string shot_uri;
		if (true == media.GetSnapshotUri(PROFILE_TOKEN,shot_uri)) {
			std::cout << "The shot uri is:" << shot_uri << std::endl;
		//	UrlToFile(shot_uri)	;
		} else {
			std::cout << "The GetSnapsshotUri is failed" << std::endl;
		}
		std::cout << std::endl << std::endl;
	}

	//add pex configuration
	/* { */
	/* 	if (false == media.AddPTZConfiguration(PROFILE_TOKEN,PTZ_CONF_TOKEN)) { */
	/* 		std::cout << "AddPTZConfiguration failed" << std::endl; */
	/* 	} else { */
	/* 		std::cout << "AddPTZConfiguration successed" << std::endl; */
	/* 	} */
	/* 	std::cout << std::endl << std::endl; */
	/* } */

	OnvifClientPTZ ptz(url.ptzXAddr,USERNAME,PASSWORD);

	//get ptz configurations
	/* { */
	/* 	std::vector<_ocp_PTZConfiguration> confs; */
	/* 	if (true == ptz.GetConfigurations(confs)) { */
	/* 		for (int i = 0; i < confs.size(); ++i) { */
	/* 			std::cout << confs[i].token << std::endl; */
	/* 			std::cout << confs[i].PanTiltLimits_x.first << "  " */ 
	/* 				<< confs[i].PanTiltLimits_x.second << std::endl; */
	/* 			std::cout << confs[i].PanTiltLimits_y.first << "  " */ 
	/* 				<< confs[i].PanTiltLimits_y.second << std::endl; */
	/* 			std::cout << confs[i].ZoomLimits.first << "  " */ 
	/* 				<< confs[i].ZoomLimits.second << std::endl; */
	/* 		} */
	/* 	} */
	/* 	std::cout << std::endl << std::endl; */
	/* } */

	//relativemove
	/* { */
	/* 	if (false == ptz.RelativeMove(PROFILE_TOKEN,0.986,0.658,0)) { */
	/* 		std::cout << "RelativeMove failed" << std::endl; */
	/* 	} else { */
	/* 		std::cout << "RelativeMove successed" << std::endl; */
	/* 	} */
	/* 	std::cout << std::endl << std::endl; */
	/* } */

	//absolutemove
	/* { */

	/* 	if (false == ptz.AbsoluteMove(PROFILE_TOKEN,0.9,0.8,0.3)) { */
	/* 		std::cout << "AbsoluteMove failed" << std::endl; */
	/* 	} else { */
	/* 		std::cout << "AbsoluteMove successed" << std::endl; */
	/* 	} */
	/* 	std::cout << std::endl << std::endl; */
	/* } */

	//goto homeposition
	/* { */

	/* 	if (false == ptz.GotoHomePosition(PROFILE_TOKEN)) { */
	/* 		std::cout << "GotoHome failed" << std::endl; */
	/* 	} else { */
	/* 		std::cout << "GotoHome successed" << std::endl; */
	/* 	} */
	/* 	std::cout << std::endl << std::endl; */
	/* } */

	//continuousmove
	/* { */
	/* 	if (false == ptz.ContinuousMove(PROFILE_TOKEN,0.12,0.3,1)) { */
	/* 		std::cout << "ContimuosMove failed" << std::endl; */
	/* 	} else { */
	/* 		std::cout << "ContimuosMove successed" << std::endl; */
	/* 	} */
	/* 	std::cout << std::endl << std::endl; */
	/* } */


	//stop
	/* { */
	/* 	if (false == ptz.Stop(PROFILE_TOKEN)) { */
	/* 		std::cout << "Stop failed" << std::endl; */
	/* 	} else { */
	/* 		std::cout << "Stop successed" << std::endl; */
	/* 	} */
	/* 	std::cout << std::endl << std::endl; */
	/* } */

	//get ptz status
	/* { */
	/* 	_ocp_PTZStatus status; */
	/* 	if (true == ptz.GetStatus(PROFILE_TOKEN,status)) { */
	/* 		std::cout << status.ptz_pan  << std::endl; */
	/* 		std::cout << status.ptz_tilt << std::endl; */
	/* 		std::cout << status.ptz_zoom << std::endl; */
	/* 		std::cout << status.move_status_pan  << std::endl; */
	/* 		std::cout << status.move_status_tilt << std::endl; */
	/* 		std::cout << status.move_status_zoom << std::endl; */
	/* 	} else { */
	/* 		std::cout << "Get Status failed" << std::endl; */
	/* 	} */

	/* } */


	//device discovery
	/* OnvifClientRemoteDiscovery discovery; */
	/* std::vector<_ocp__Device> devices; */
	/* if (true == discovery.ProbeMatch(devices,3)) { */

	/* 	for (auto iter : devices) { */
	/* 		std::cout << "IPV4:" << iter.IPv4 << std::endl; */
	/* 		std::cout << "UUID:" << iter.UUID << std::endl; */
	/* 		for (auto subiter : iter.WsddUris) { */
	/* 			std::cout << "URIS:" << subiter << std::endl; */
	/* 		} */
	/* 		std::cout << std::endl << std::endl; */	
	/* 	} */
	/* } */

}



int main()
{
		OnvifPackageDemo();

	return 0;
}

/*use opencv and curl to save image */
/* #include <curl/curl.h> */
/* #include <opencv2/opencv.hpp> */

/* size_t write_data(char* ptr, size_t size, size_t nmemb, std::vector<char>& userdata) { */
/* 	size_t count = size * nmemb; */
/* 	for (int i = 0; i < count; ++i) { */
/* 		userdata.push_back(ptr[i]); */
/* 	} */
/* 	return count; */
/* } */

//the param url is the uri from getsnapshoturi
/* void UrlToFile(const std::string url) { */

/* 	std::vector<char> userdata; */
/* 	curl_global_init(CURL_GLOBAL_DEFAULT); */
/* 	CURL* curl; */
/* 	CURLcode res; */
/* 	curl = curl_easy_init(); */
/* 	curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); */
/* 	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data); */
/* 	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &userdata); */

/* 	const std::string userpwd = "admin:Thinkjoy"; */
/* 	curl_easy_setopt(curl, CURLOPT_USERPWD,userpwd.c_str()); */


/* 	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false); */
/* 	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false); */

/* 	res = curl_easy_perform(curl); */
/* 	if (res != CURLE_OK) { */
/* 		fprintf(stderr, "curl_easy_perform() failed: %s\n", */
/* 				curl_easy_strerror(res)); */
/* 	} */
/* 	curl_easy_cleanup(curl); */

/* 	std::cout << userdata.size() << std::endl; */

/* 	cv::Mat src_img = cv::imdecode(userdata, cv::IMREAD_ANYCOLOR); */
/* 	cv::imwrite("thinkjoy.jpeg",src_img); */
/* } */
