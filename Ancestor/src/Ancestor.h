#pragma once

//For use by Ancestor Applications

#include <stdio.h>
#include "Ancestor/Application.h"
#include "Ancestor/Log.h"
#include "Ancestor/Layer.h"

#include "Ancestor/Input.h"
#include "Ancestor/KeyCodes.h"
#include "Ancestor/MouseButtonCodes.h"

//--------------Event---------------
#include "Ancestor/Events/KeyEvent.h"
#include "Ancestor/Events/MouseEvent.h"
//----------------------------------

#include "Ancestor/ImGui/ImGuiLayer.h"

// -------------Renderer------------
#include "Ancestor/Renderer/Renderer.h"
#include "Ancestor/Renderer/RenderCommand.h"
#include "Ancestor/Renderer/Camera.h"
#include "Ancestor/Renderer/Shader.h"
#include "Ancestor/Renderer/Texture.h"
#include "Ancestor/Renderer/Model.h"

// ---------------------------------

//-----------Entry Point------------------
#include "Ancestor/EntryPoint.h"
//----------------------------------------