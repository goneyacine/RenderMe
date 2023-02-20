#pragma once


namespace RenderMe

{

	namespace Base {

		struct TransformComponent
		{
			//entity position
			float x_position = 0;
			float y_position = 0;
			float z_position = 0;

			//entity rotation
			float x_rotation = 0;
			float y_rotation = 0;
			float z_rotation = 0;

			//entity scale 
			float x_scale = 0;
			float y_scale = 0;
			float z_scale = 0;
		};

	}
}