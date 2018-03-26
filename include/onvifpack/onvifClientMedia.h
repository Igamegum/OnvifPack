#ifndef ONVIF_CLIENT_MEDIA_H_
#define ONVIF_CLIENT_MEDIA_H_

#include <string>
#include <vector>
#include <soapMediaBindingProxy.h>

struct _ocp_Profile {
	std::string profileName;
	std::string profileToken;
};
struct _ocp_VideoSourceConfigurations {
	std::string token;
};

struct _ocp_VideoEncoderConfigurations {
	std::string token;
};

class OnvifClientMedia {
	private:
	std::string _ocp_password;
	std::string _ocp_username;
	std::string _ocp_soap_endpoint;
	MediaBindingProxy proxyMedia;
	public:
	OnvifClientMedia(const std::string &,const std::string &,const std::string &) ;
	bool AddPTZConfiguration(const std::string &,const std::string &);
	bool AddVideoSourceConfiguration(const std::string &,const std::string &);
	bool AddVideoEncoderConfiguration(const std::string &,const std::string &);
	bool CreateProfile(const std::string &,std::string &);
	bool DeleteProfile(const std::string &);
	bool GetProfiles(std::vector<_ocp_Profile> &);
	bool GetVideoSourceConfigurations(std::vector<_ocp_VideoSourceConfigurations> &);
	bool GetVideoEncoderConfigurations(std::vector<_ocp_VideoEncoderConfigurations> &);
	bool GetSnapshotUri(const std::string &,std::string &);

};

#endif
