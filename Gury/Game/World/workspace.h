#pragma once

#include <G3DAll.h>
#include <vector>

#include "../Gury/Game/Rendering/renderScene.h"
#include "../Gury/Game/Objects/model.h"

#include "ICameraOwner.h"
#include "camera.h"

#include "extents.h"

namespace RBX
{

	class Workspace :
		public RBX::ModelInstance,
		public RBX::Service<Workspace>
	{
	private:
		Camera* currentCamera;
	public:
		/* deprecated, use Datamodel->workspace */

		static Workspace* get();

		void wakeUpModels();

		static void workspaceDescendentAdded(RBX::Instance* descendent);
		static void workspaceDescendentRemoved(RBX::Instance* descendent);

		void createCurrentCamera();
		Camera* getCurrentCamera();

		bool setImageServerView();
		Render::Geometry getBoundingBox()
		{
			return Render::Geometry();
		}

		virtual RBX::ModelInstance* getModel() { return this; }
		virtual RBX::Extents computeCameraOwnerExtents();

		Workspace()
		{
			setClassName("Workspace");
			setName("Workspace");

			onDescendentAdded.connect(workspaceDescendentAdded);
			onDescendentRemoved.connect(workspaceDescendentRemoved);

			isParentLocked = 1;
			isSelectable = false;

		}

		RTTR_ENABLE(ModelInstance)
	};
	void getPVInstances(RBX::Instances* instances, RBX::Instances* pvs);
}