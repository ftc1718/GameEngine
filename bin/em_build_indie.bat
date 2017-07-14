em++ -std=c++11 -I"..\Dependencies\Freeimage\include" "..\Indie-core\src\graphics\buffers\buffer.cpp" "..\Indie-core\src\graphics\buffers\indexBuffer.cpp" "..\Indie-core\src\graphics\buffers\vertexArray.cpp" "..\Indie-core\src\graphics\layers\group.cpp" "..\Indie-core\src\graphics\layers\layer.cpp" "..\Indie-core\src\graphics\batchRenderer2d.cpp" "..\Indie-core\src\graphics\font.cpp" "..\Indie-core\src\graphics\fontManager.cpp" "..\Indie-core\src\graphics\label.cpp" "..\Indie-core\src\graphics\shader.cpp" "..\Indie-core\src\graphics\sprite.cpp"  "..\Indie-core\src\graphics\texture.cpp" "..\Indie-core\src\graphics\window.cpp" "..\Indie-core\src\maths\mat4.cpp" "..\Indie-core\src\maths\vec2.cpp" "..\Indie-core\src\maths\vec3.cpp" "..\Indie-core\src\maths\vec4.cpp" "..\Indie-core\src\utility\fileUtils.cpp" "..\Indie-core\src\utility\stringUtils.cpp" "..\Indie-core\examples\game.cpp" "..\Indie-core\examples\gameMain.cpp" "..\Dependencies\Freetype-Emscripten\freetype.bc" "..\Dependencies\FreeImage-Emscripten\freeimage.bc" -s USE_GLFW=3 -s FULL_ES3=1 -DINDIE_EMSCRIPTEN=1 --memory-init-file 0 --embed-file res -O3 -o Web\Indie.html