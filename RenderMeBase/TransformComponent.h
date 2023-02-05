#pragma once


namespace RenderMe

{

	namespace Base {

		struct TransformComponent
		{
			//entity position
			float x_position;
			float y_position;
			float z_position;

			//entity rotation
			float x_rotation;
			float y_rotation;
			float z_rotation;

			//entity scale 
			float x_scale;
			float y_scale;
			float z_scale;
		};

	}
}