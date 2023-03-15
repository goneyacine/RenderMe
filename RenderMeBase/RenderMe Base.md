# RenderMe Base

RenderMe Base contains some basic components that are used by the 2D and 3D renderers like TexturesManager, Entity, and Scene...

## How to use it?
### Entity :
an Entity is just an ID (```std::uint32_t```) that will be added to a scene so you can attach components to it
 
To Create an Entity 

```cpp
#include "Entity.h"
#include "Scene.h"
```
then
```cpp
RenderMe::Base::Scene scene();
//this will create an entity, attach it to the scene and return its ID
RenderMe::Entity entity = scene.addEntity();
```

### Transform Component :



### Scene :

Scene stores all the Entities that will be rendered and contains a registry where all Entity components are stored

   the Scene class is in the ```Scene.h``` header file, so to use it add ```#include "Scene.h"```

   #### Create a Scene :
   ```cpp
   RenderMe::Base::Scene scene();
   ```
   #### Adding And Remove Entities :

   To create and add an entity :
   ```cpp
   RenderMe::Entity entity = scene.addEntity();
   ```
   And to remove it :
   ```cpp
   scene.removeEntity(entity);
   ```

   #### Adding and Getting Components :

   To add components :
   ```cpp
   ExampleComponent component();
   scene.addComponent<ExampleComponent>(entity,component);
   ```
   this will attach ```component``` to ```entity```, and if the entity already has a component of the same type it will replace it with the new one.

   To get component :
   ```cpp
   ExampleComponent* component = scene.getComponent<ExampleComponent>(entity);
   ```
   this will return ```nullptr``` if the component of type ```ExampleComponent``` is not attached to ```entity```
  

### TexturesManager :

 To be able to use textures in your application you need to load them using ```RenderMe::Base::TexturesManager ```, every texture has a unique id.

 #### How to use it? 

  First, include ```TexturesManager.h``` :
  ```cpp
  #include "TexturesManager.h"
  ```
  then : 

  ```cpp 
  TexturesManager texturesManager = TexturesManager();
  texturesManager.addTexture("TEXTURE FILE PATH HERE", "texture_name");
  ```
  the ```addTexture``` function takes two parameters, the first one is the file path of the image file, and the second is the texture's name, you will use that name to get your texture's id at any time.
   
  to get access to your texture use :  
  ```cpp
  texturesManager.getTexture("texture_name");
  ```
  this will return ```RenderMe::Base::Texture``` object.

### ShadersManager :

 ```RenderMe::Base::ShadersManager``` is used to compile shaders.

 every scene has its own shaders manager and you don't create one, to compile shader just use :
 ```cpp
  scene.getShadersManager()->compileShader_by_filePath("ExampleVertexShaderName",GL_VERTEX_SHADER,"SOURCE_FILE_PATH_HERE");
  ```
  and to get access to the shader : 
  ```cpp 
   unsigned int vertexShader = scene.getShadersManager()->getShader("ExampleVertexShader");
  ```

