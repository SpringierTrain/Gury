#include "motor.h"

void RBX::MotorConnector::build()
{
	if (!body0 || !body1 
		|| (body0 && !body0->body) || (body1 && !body1->body)) return;

	motor = dJointCreateAMotor(Gurnel::get()->world, JointsService::get()->joints);

	dJointAttach(motor, body0->body, body1->body);
}