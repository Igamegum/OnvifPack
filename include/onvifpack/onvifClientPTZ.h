#ifndef ONVIF_CLIENT_PTZ_H_
#define ONVIF_CLIENT_PTZ_H_


#include <string>
#include <soapPTZBindingProxy.h>

typedef struct {
	float speed_x;
	float speed_y;
	float speed_z;
}_ocp_PTZSpeed;


typedef struct {
	std::string            name;
	std::string            token;
	std::string            nodeToken;
	std::string            defaultAbsolutePantTiltPositionSpace;
	std::string            defaultAbsoluteZoomPositionSpace;
	std::string            defaultRelativePanTiltTranslationSpace;
	std::string            defaultRelativeZoomTranslationSpace;
	std::string            defaultContinuousPanTiltVelocitySpace;
	std::string            defaultContinuousZoomVelocitySpace;
	_ocp_PTZSpeed          defaultPTZSpeed;
	long long              defaultPTZTimeout;
	std::pair<float,float> PanTiltLimits_x;
	std::pair<float,float> PanTiltLimits_y;
	std::pair<float,float> ZoomLimits;
}_ocp_PTZConfiguration;


typedef struct {
	float ptz_pan;
	float ptz_tilt;
	float ptz_zoom;
	tt__MoveStatus move_status_pan;
	tt__MoveStatus move_status_tilt;
	tt__MoveStatus move_status_zoom;
}_ocp_PTZStatus;

class OnvifClientPTZ {

	private:
	std::string _ocp_password;
	std::string _ocp_username;
	std::string _ocp_soap_endpoint;
	PTZBindingProxy proxyPTZ;
	public:
	OnvifClientPTZ(const std::string &,const std::string &,const std::string &);
	bool ContinuousMove(const std::string &,
	                    const float &,
	                    const float &,
	                    const float &,
	                    const long long & timeout = 0);
	
	bool Stop(const std::string &,
	          const bool & stopPanTilt = true,
	          const bool & stopZoom = true);
	
	bool AbsoluteMove(const std::string &,
	                  const float &,
	                  const float &,
	                  const float &,
	                  const float & speed_x = 0.0f,
	                  const float & speed_y = 0.0f,
	                  const float & speed_z = 0.0f);
	
	bool RelativeMove(const std::string &,
	                  const float &,
	                  const float &,
	                  const float &,
	                  const float & speed_x = 0.0f,
	                  const float & speed_y = 0.0f,
	                  const float & speed_z = 0.0f);
	
	bool GotoHomePosition(const std::string &,
	                      const float & speed_x = 0.0f,
	                      const float & speed_y = 0.0f,
	                      const float & speed_z = 0.0f);

	bool GetConfigurations(std::vector<_ocp_PTZConfiguration> &);

	bool GetStatus(const std::string &,_ocp_PTZStatus &);

};


#endif
