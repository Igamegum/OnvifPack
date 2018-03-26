#include <onvifClientMedia.h>
#include <wsseapi.h>
#include <ErrorLog.h>


OnvifClientMedia::OnvifClientMedia(const std::string & soap_endpoint,
                                   const std::string & username,
                                   const std::string & password) {

	_ocp_soap_endpoint = soap_endpoint;
	_ocp_username = username;
	_ocp_password = password;
	proxyMedia.soap_endpoint = _ocp_soap_endpoint.c_str();
	soap_register_plugin(proxyMedia.soap, soap_wsse);

}

bool OnvifClientMedia::GetProfiles(std::vector<_ocp_Profile> & __profiles) {

	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyMedia.soap, NULL, _ocp_username.c_str(), _ocp_password.c_str())) {
//		PrintErr(proxyMedia.soap);
		return false;
	}

	struct soap* soap = soap_new();
	_trt__GetProfiles * request = soap_new__trt__GetProfiles(soap);
	_trt__GetProfilesResponse * response = soap_new__trt__GetProfilesResponse(soap);

	bool execute_result = true;

		__profiles.clear();
	if (SOAP_OK == proxyMedia.GetProfiles(request,response)) {
		for (int i = 0; i < response->Profiles.size(); ++i) {
			_ocp_Profile profile; 
			profile.profileName = response->Profiles[i]->Name;
			profile.profileToken = response->Profiles[i]->token;
			__profiles.emplace_back(profile);
		}
		execute_result = true;
	} else {
//		PrintErr(proxyMedia.soap);
		execute_result = false;
	}

	soap_destroy(soap);
	soap_end(soap);
	return execute_result;
}

bool OnvifClientMedia::CreateProfile(const std::string & profileName,
                                     std::string & profileToken) {

	bool user_defined_token = profileToken.length() > 0 ? true : false;

	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyMedia.soap, NULL, _ocp_username.c_str(), _ocp_password.c_str())) {
//		PrintErr(proxyMedia.soap);
		return false;
	}

	struct soap*soap = soap_new();

	_trt__CreateProfile *trt__CreateProfile = soap_new__trt__CreateProfile(soap, -1);
	_trt__CreateProfileResponse *trt__CreateProfileResponse = soap_new__trt__CreateProfileResponse(soap, -1);

	trt__CreateProfile->Name = profileName;
	if (user_defined_token) {
		trt__CreateProfile->Token = &profileToken;
	}

	bool execute_result = true;

	if (SOAP_OK == proxyMedia.CreateProfile(trt__CreateProfile, trt__CreateProfileResponse)) { 
		if (false == user_defined_token) {
			profileToken = trt__CreateProfileResponse->Profile->token;
		}
		std::cout << "name:" << trt__CreateProfileResponse->Profile->Name << "  token:" << trt__CreateProfileResponse->Profile->token << std::endl;
	} else {
//		PrintErr(proxyMedia.soap);
		execute_result = false;
	}


	soap_destroy(soap);
	soap_end(soap);

	return execute_result;
}

bool OnvifClientMedia::DeleteProfile(const std::string & profileToken) {

	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyMedia.soap, NULL, _ocp_username.c_str(), _ocp_password.c_str())) {
//		PrintErr(proxyMedia.soap);
		return false;
	}

	struct soap* soap = soap_new();
	_trt__DeleteProfile * request = soap_new__trt__DeleteProfile(soap);
	request->ProfileToken = profileToken;
	_trt__DeleteProfileResponse * response = soap_new__trt__DeleteProfileResponse(soap);

	bool execute_result = true;
	if (SOAP_OK == proxyMedia.DeleteProfile(request,response)) {
	} else {
//		PrintErr(proxyMedia.soap);
        execute_result = false;
	}
	
	soap_destroy(soap);
	soap_end(soap);
	return execute_result;
}

bool OnvifClientMedia::GetVideoSourceConfigurations(
		std::vector<_ocp_VideoSourceConfigurations>& videoSoureConfigurations) {

	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyMedia.soap, NULL, _ocp_username.c_str(), _ocp_password.c_str())) {
//		PrintErr(proxyMedia.soap);
		return false;
	}

	struct soap* soap = soap_new();
	_trt__GetVideoSourceConfigurations * request = soap_new__trt__GetVideoSourceConfigurations(soap);
	_trt__GetVideoSourceConfigurationsResponse * response = soap_new__trt__GetVideoSourceConfigurationsResponse(soap);
    
	bool execute_result = true;
	if (SOAP_OK == proxyMedia.GetVideoSourceConfigurations(request,response)) {
		for (int i = 0; i < response->Configurations.size(); ++i) {
			_ocp_VideoSourceConfigurations conf;
			conf.token = response->Configurations[i]->token;
			videoSoureConfigurations.emplace_back(conf);
		}
	} else {
//		PrintErr(proxyMedia.soap);
		execute_result = false;
	}
	soap_destroy(soap);
	soap_end(soap);
	return execute_result;

}

bool OnvifClientMedia::GetVideoEncoderConfigurations(
		std::vector<_ocp_VideoEncoderConfigurations> & videoEncoderConfigurations) {

	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyMedia.soap, NULL, _ocp_username.c_str(), _ocp_password.c_str())) {
		PrintErr(proxyMedia.soap);
		return false;
	}

	struct soap* soap = soap_new();
	_trt__GetVideoEncoderConfigurations * request = soap_new__trt__GetVideoEncoderConfigurations(soap);
	_trt__GetVideoEncoderConfigurationsResponse * response = soap_new__trt__GetVideoEncoderConfigurationsResponse(soap);

	bool execute_result = true;
	if (SOAP_OK == proxyMedia.GetVideoEncoderConfigurations(request,response)) {
		for (int i = 0; i < response->Configurations.size(); ++i) {
			_ocp_VideoEncoderConfigurations conf;
			conf.token = response->Configurations[i]->token;
			videoEncoderConfigurations.emplace_back(conf);
		}
	} else {
		PrintErr(proxyMedia.soap);
		execute_result = false;
	}
	soap_destroy(soap);
	soap_end(soap);
	return execute_result;
}




bool OnvifClientMedia::AddPTZConfiguration(const std::string & profileToken,
                                           const std::string & configurationToken) {

	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyMedia.soap, NULL, _ocp_username.c_str(), _ocp_password.c_str())) {
//		PrintErr(proxyMedia.soap);
		return false;
	}

	struct soap*soap = soap_new();
	_trt__AddPTZConfiguration *trt__AddPTZConfiguration = soap_new__trt__AddPTZConfiguration(soap, -1);
	_trt__AddPTZConfigurationResponse *trt__AddPTZConfigurationResponse = soap_new__trt__AddPTZConfigurationResponse(soap, -1);

	trt__AddPTZConfiguration->ProfileToken = profileToken;	
	trt__AddPTZConfiguration->ConfigurationToken = configurationToken;


	bool execute_result = true;
	if (SOAP_OK == proxyMedia.AddPTZConfiguration(trt__AddPTZConfiguration, trt__AddPTZConfigurationResponse)) {
	} else {
//		PrintErr(proxyMedia.soap);
		execute_result = false;
	}

	soap_destroy(soap);
	soap_end(soap);
	return execute_result;
}
bool OnvifClientMedia::AddVideoSourceConfiguration(const std::string & profileToken,
                                                   const std::string & configurationToken) {

	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyMedia.soap, NULL, _ocp_username.c_str(), _ocp_password.c_str())) {
		PrintErr(proxyMedia.soap);
		return false;
	}

	struct soap * soap = soap_new();

	_trt__AddVideoSourceConfiguration *request = soap_new__trt__AddVideoSourceConfiguration(soap, -1);
	_trt__AddVideoSourceConfigurationResponse *response = soap_new__trt__AddVideoSourceConfigurationResponse(soap, -1);

	request->ProfileToken = profileToken;	
	request->ConfigurationToken = configurationToken;

	bool execute_result = true;
	if (SOAP_OK == proxyMedia.AddVideoSourceConfiguration(request, response)) {
	} else {
		execute_result = false;
		PrintErr(proxyMedia.soap);
	}

	soap_destroy(soap);
	soap_end(soap);
	return execute_result;
}



bool OnvifClientMedia::AddVideoEncoderConfiguration(const std::string & profileToken,
                                                    const std::string & configurationToken) {

	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyMedia.soap, NULL, _ocp_username.c_str(), _ocp_password.c_str())) {
		PrintErr(proxyMedia.soap);
		return false;
	}

	struct soap * soap = soap_new();

	_trt__AddVideoEncoderConfiguration *request = soap_new__trt__AddVideoEncoderConfiguration(soap, -1);
	_trt__AddVideoEncoderConfigurationResponse *response = soap_new__trt__AddVideoEncoderConfigurationResponse(soap, -1);

	request->ProfileToken = profileToken;	
	request->ConfigurationToken = configurationToken;

	bool execute_result = true;
	if (SOAP_OK == proxyMedia.AddVideoEncoderConfiguration(request, response)) {
	} else {
		execute_result = false;
		PrintErr(proxyMedia.soap);
	}

	soap_destroy(soap);
	soap_end(soap);
	return execute_result;
}

bool OnvifClientMedia::GetSnapshotUri(const std::string& profileToken,std::string & shot_uri) {

	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyMedia.soap, NULL, _ocp_username.c_str(), _ocp_password.c_str())) {
		PrintErr(proxyMedia.soap);
		return false;
	}
	struct soap * soap = soap_new();
	_trt__GetSnapshotUri *request = soap_new__trt__GetSnapshotUri(soap);
	request->ProfileToken = profileToken;

	_trt__GetSnapshotUriResponse * response = soap_new__trt__GetSnapshotUriResponse(soap);
	bool execute_result = false;
	if (SOAP_OK == proxyMedia.GetSnapshotUri(request,response)) {
		execute_result = true;
		shot_uri = response->MediaUri->Uri;
	} else {
		PrintErr(proxyMedia.soap);
	}
	soap_destroy(soap);
	soap_end(soap);
	return execute_result;
}
