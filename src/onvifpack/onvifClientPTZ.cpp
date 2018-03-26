#include <onvifClientPTZ.h>
#include <wsseapi.h>
#include <ErrorLog.h>

OnvifClientPTZ::OnvifClientPTZ(const std::string & soap_endpoint,
                               const std::string & username,
                               const std::string & password) {
	_ocp_soap_endpoint = soap_endpoint;
	_ocp_username = username;
	_ocp_password = password;
	proxyPTZ.soap_endpoint = _ocp_soap_endpoint.c_str();
	soap_register_plugin(proxyPTZ.soap, soap_wsse);

}


bool OnvifClientPTZ::ContinuousMove(const std::string & profileToken,
                                    const float & speed_x,
                                    const float & speed_y,
                                    const float & zoom,
                                    const long long & timeout) {
	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyPTZ.soap, NULL,_ocp_username.c_str(),_ocp_password.c_str())) {
		PrintErr(proxyPTZ.soap);
		return false;
	}
	

	struct soap*soap = soap_new();
	//构造参数
	_tptz__ContinuousMove* moveRequest = soap_new__tptz__ContinuousMove(soap);

	tt__ReferenceToken token = profileToken;
	moveRequest->ProfileToken = token;

	moveRequest->Velocity = soap_new_tt__PTZSpeed(soap);
	moveRequest->Velocity->PanTilt = soap_new_tt__Vector2D(soap);
	moveRequest->Velocity->PanTilt->x = speed_x;
	moveRequest->Velocity->PanTilt->y = speed_y;
	
	moveRequest->Velocity->Zoom = soap_new_tt__Vector1D(soap);
	moveRequest->Velocity->Zoom->x = zoom;

	moveRequest->Timeout = (xsd__duration *)soap_malloc(soap,sizeof(xsd__duration*));
	*moveRequest->Timeout = timeout;

	bool execute_result = true;

	 _tptz__ContinuousMoveResponse* moveResponse =  soap_new__tptz__ContinuousMoveResponse(soap);

	int move_result = proxyPTZ.ContinuousMove(moveRequest,moveResponse);

	if (move_result == SOAP_OK) {
	} else {
		PrintErr(proxyPTZ.soap);
		execute_result = false;
	}

	soap_destroy(soap);
	soap_end(soap);

	return execute_result;
}

bool OnvifClientPTZ::Stop(const std::string & profileToken,
                          const bool & stopPanTilt,
                          const bool & stopZoom) {

	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyPTZ.soap, NULL,_ocp_username.c_str(),_ocp_password.c_str())) {
		PrintErr(proxyPTZ.soap);
		return false;
	}

	struct soap*soap = soap_new();
	//构造参数
	_tptz__Stop* moveRequest = soap_new__tptz__Stop(soap);
	tt__ReferenceToken token = profileToken;
	moveRequest->ProfileToken = token;
	moveRequest->PanTilt = (bool*)soap_malloc(soap, sizeof(bool*));
	moveRequest->Zoom = (bool*)soap_malloc(soap, sizeof(bool*));
	*moveRequest->PanTilt = stopPanTilt;
	*moveRequest->Zoom = stopZoom;

	 _tptz__StopResponse* moveResponse = soap_new__tptz__StopResponse(soap);

	bool execute_result = true;
	int move_result = proxyPTZ.Stop(moveRequest,moveResponse);

	if (move_result == SOAP_OK) {
	} else {
		execute_result = false;
	}

	soap_destroy(soap);
	soap_end(soap);

	return execute_result;
}

bool OnvifClientPTZ::AbsoluteMove(const std::string & profileToken,
                                  const float & PanTilt_x,
                                  const float & PanTilt_y,
                                  const float & Zoom,
                                  const float & speed_x,
                                  const float & speed_y,
                                  const float & speed_z) {

	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyPTZ.soap, NULL,_ocp_username.c_str(),_ocp_password.c_str())) {
		PrintErr(proxyPTZ.soap);
		return false;
	}

	struct soap*soap = soap_new();
	//构造参数
	_tptz__AbsoluteMove* moveRequest = soap_new__tptz__AbsoluteMove(soap);

	tt__ReferenceToken token = profileToken;
	moveRequest->ProfileToken = token;

	moveRequest->Position = soap_new_tt__PTZVector(soap);
	moveRequest->Position->PanTilt = soap_new_tt__Vector2D(soap);
	moveRequest->Position->PanTilt->x = PanTilt_x;
	moveRequest->Position->PanTilt->y = PanTilt_y;
	moveRequest->Position->Zoom = soap_new_tt__Vector1D(soap);
	moveRequest->Position->Zoom->x = Zoom;

	moveRequest->Speed = soap_new_tt__PTZSpeed(soap);
	moveRequest->Speed->PanTilt = soap_new_tt__Vector2D(soap);
	moveRequest->Speed->PanTilt->x = speed_x;
	moveRequest->Speed->PanTilt->y = speed_y;
	moveRequest->Speed->Zoom = soap_new_tt__Vector1D(soap);
	moveRequest->Speed->Zoom->x = speed_z;


	_tptz__AbsoluteMoveResponse* moveResponse =  soap_new__tptz__AbsoluteMoveResponse(soap);
	
	bool execute_result = true;
	int move_result = proxyPTZ.AbsoluteMove(moveRequest,moveResponse);

	if (move_result == SOAP_OK) {
//		std::cout << "AbsoluteMove OK" << std::endl;
	} else {
		PrintErr(proxyPTZ.soap);
		execute_result = false;
	}

	soap_destroy(soap);
	soap_end(soap);

	return execute_result;
}

bool OnvifClientPTZ::RelativeMove(const std::string & profileToken,
                                  const float & PanTilt_x,
                                  const float & PanTilt_y,
                                  const float & Zoom,
                                  const float & speed_x,
                                  const float & speed_y,
                                  const float & speed_z) {

	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyPTZ.soap, NULL,_ocp_username.c_str(),_ocp_password.c_str())) {
		PrintErr(proxyPTZ.soap);
		return false;
	}

	struct soap*soap = soap_new();
	//构造参数
	_tptz__RelativeMove* moveRequest = soap_new__tptz__RelativeMove(soap);

	tt__ReferenceToken token = profileToken;
	moveRequest->ProfileToken = token;

	moveRequest->Translation = soap_new_tt__PTZVector(soap);
	moveRequest->Translation->PanTilt = soap_new_tt__Vector2D(soap);
	moveRequest->Translation->PanTilt->x = PanTilt_x;
	moveRequest->Translation->PanTilt->y = PanTilt_y;
	moveRequest->Translation->Zoom = soap_new_tt__Vector1D(soap);
	moveRequest->Translation->Zoom->x = Zoom;

	moveRequest->Speed = soap_new_tt__PTZSpeed(soap);
	moveRequest->Speed->PanTilt = soap_new_tt__Vector2D(soap);
	moveRequest->Speed->PanTilt->x = speed_x;
	moveRequest->Speed->PanTilt->y = speed_y;
	moveRequest->Speed->Zoom = soap_new_tt__Vector1D(soap);
	moveRequest->Speed->Zoom->x = speed_z;

	_tptz__RelativeMoveResponse* moveResponse =  soap_new__tptz__RelativeMoveResponse(soap);
	

	bool execute_result = true;
	if (SOAP_OK == proxyPTZ.RelativeMove(moveRequest,moveResponse)) {
//		std::cout << "RelativeMove success" << std::endl;
	} else {
		PrintErr(proxyPTZ.soap);
		execute_result = false;
	}

	soap_destroy(soap);
	soap_end(soap);
	return execute_result;
}

bool OnvifClientPTZ::GotoHomePosition(const std::string & profileToken,
                                      const float & speed_x,
                                      const float & speed_y,
                                      const float & speed_z) {

	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyPTZ.soap, NULL,_ocp_username.c_str(),_ocp_password.c_str())) {
		PrintErr(proxyPTZ.soap);
		return false;
	}

	struct soap*soap = soap_new();
	//构造参数
	_tptz__GotoHomePosition* moveRequest = soap_new__tptz__GotoHomePosition(soap);

	tt__ReferenceToken token = profileToken;
	moveRequest->ProfileToken = token;

	moveRequest->Speed = soap_new_tt__PTZSpeed(soap);
	moveRequest->Speed->PanTilt = soap_new_tt__Vector2D(soap);
	moveRequest->Speed->PanTilt->x = speed_x;
	moveRequest->Speed->PanTilt->y = speed_y;
	moveRequest->Speed->Zoom = soap_new_tt__Vector1D(soap);
	moveRequest->Speed->Zoom->x = speed_z;

	 _tptz__GotoHomePositionResponse* moveResponse = soap_new__tptz__GotoHomePositionResponse(soap);

	bool execute_result = true;

	if (proxyPTZ.GotoHomePosition(moveRequest,moveResponse)== SOAP_OK) {
		std::cout << "GotoHome OK" << std::endl;
	} else {
		PrintErr(proxyPTZ.soap);
		execute_result = false;
	}

	soap_destroy(soap);
	soap_end(soap);
	return execute_result;

}

bool OnvifClientPTZ::GetConfigurations(std::vector<_ocp_PTZConfiguration> & configurations) {

	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyPTZ.soap, NULL,_ocp_username.c_str(),_ocp_password.c_str())) {
		PrintErr(proxyPTZ.soap);
		return false;
	}

	struct soap*soap = soap_new();
	_tptz__GetConfigurations * confRequest = soap_new__tptz__GetConfigurations(soap);
	_tptz__GetConfigurationsResponse *confResponse = soap_new__tptz__GetConfigurationsResponse(soap);

	bool execute_result = true;
	if (SOAP_OK == proxyPTZ.GetConfigurations(confRequest,confResponse)) {

		configurations.clear();
		for (int i = 0; i < confResponse->PTZConfiguration.size(); ++i) {

			_ocp_PTZConfiguration conf;

			conf.name = confResponse->PTZConfiguration[i]->Name;
			conf.token = confResponse->PTZConfiguration[i]->token;
			conf.nodeToken = confResponse->PTZConfiguration[i]->NodeToken;
			conf.defaultAbsolutePantTiltPositionSpace = *(confResponse->PTZConfiguration[i]->DefaultAbsolutePantTiltPositionSpace);
			conf.defaultAbsoluteZoomPositionSpace = *(confResponse->PTZConfiguration[i]->DefaultAbsoluteZoomPositionSpace);
			conf.defaultRelativePanTiltTranslationSpace = *(confResponse->PTZConfiguration[i]->DefaultRelativePanTiltTranslationSpace);
			conf.defaultRelativeZoomTranslationSpace = *(confResponse->PTZConfiguration[i]->DefaultRelativeZoomTranslationSpace);
			conf.defaultContinuousPanTiltVelocitySpace = *(confResponse->PTZConfiguration[i]->DefaultContinuousPanTiltVelocitySpace);
			conf.defaultContinuousZoomVelocitySpace = *(confResponse->PTZConfiguration[i]->DefaultContinuousZoomVelocitySpace);

			conf.defaultPTZSpeed.speed_x = confResponse->PTZConfiguration[i]->DefaultPTZSpeed->PanTilt->x;
			conf.defaultPTZSpeed.speed_y = confResponse->PTZConfiguration[i]->DefaultPTZSpeed->PanTilt->y;
			conf.defaultPTZSpeed.speed_z = confResponse->PTZConfiguration[i]->DefaultPTZSpeed->Zoom->x;

			conf.defaultPTZTimeout = *(confResponse->PTZConfiguration[i]->DefaultPTZTimeout);
			conf.PanTiltLimits_x = 
				std::make_pair(confResponse->PTZConfiguration[i]->PanTiltLimits->Range->XRange->Min,
						       confResponse->PTZConfiguration[i]->PanTiltLimits->Range->XRange->Max);

			conf.PanTiltLimits_y = 
				std::make_pair(confResponse->PTZConfiguration[i]->PanTiltLimits->Range->YRange->Min,
						       confResponse->PTZConfiguration[i]->PanTiltLimits->Range->YRange->Max);

			conf.ZoomLimits = 
				std::make_pair(confResponse->PTZConfiguration[i]->ZoomLimits->Range->XRange->Min,
						       confResponse->PTZConfiguration[i]->ZoomLimits->Range->XRange->Max);

			configurations.emplace_back(conf);
		}

	} else {
		PrintErr(proxyPTZ.soap);
		execute_result = false;
	}
	soap_destroy(soap);
	soap_end(soap);
	return execute_result;
}

bool OnvifClientPTZ::GetStatus(const std::string & profileToken,_ocp_PTZStatus & status) {

	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyPTZ.soap, NULL,_ocp_username.c_str(),_ocp_password.c_str())) {
		PrintErr(proxyPTZ.soap);
		return false;
	}

	struct soap*soap = soap_new();
	_tptz__GetStatus * statusRequest = soap_new__tptz__GetStatus(soap);
	_tptz__GetStatusResponse *statusResponse = soap_new__tptz__GetStatusResponse(soap);

	tt__ReferenceToken token = profileToken;
	statusRequest->ProfileToken = token;

	bool execute_result = true;
	if (SOAP_OK == proxyPTZ.GetStatus(statusRequest,statusResponse)) {
		if (statusResponse->PTZStatus) {
			if (statusResponse->PTZStatus->Position) {
				status.ptz_pan  = statusResponse->PTZStatus->Position->PanTilt->x;
				status.ptz_tilt = statusResponse->PTZStatus->Position->PanTilt->y;
				status.ptz_zoom = statusResponse->PTZStatus->Position->Zoom->x;
			} else {
				execute_result = false;
			}
			if (statusResponse->PTZStatus->MoveStatus) {
				if (statusResponse->PTZStatus->MoveStatus->PanTilt) {
					status.move_status_pan  = *(statusResponse->PTZStatus->MoveStatus->PanTilt);
					status.move_status_tilt  = *(statusResponse->PTZStatus->MoveStatus->PanTilt);
				} else {
					status.move_status_pan  = tt__MoveStatus::tt__MoveStatus__UNKNOWN; 
					status.move_status_tilt  = tt__MoveStatus::tt__MoveStatus__UNKNOWN; 
				}
				if (statusResponse->PTZStatus->MoveStatus->Zoom) {
					status.move_status_zoom  = *(statusResponse->PTZStatus->MoveStatus->Zoom);
				} else {
					status.move_status_zoom  = tt__MoveStatus::tt__MoveStatus__UNKNOWN; 
				}
			} else {
				status.move_status_pan  = tt__MoveStatus::tt__MoveStatus__UNKNOWN; 
				status.move_status_tilt  = tt__MoveStatus::tt__MoveStatus__UNKNOWN; 
				status.move_status_zoom  = tt__MoveStatus::tt__MoveStatus__UNKNOWN; 
			}
		}
	} else {
		PrintErr(proxyPTZ.soap);
		execute_result = false;
	}

	soap_destroy(soap);
	soap_end(soap);
	return execute_result;

}
