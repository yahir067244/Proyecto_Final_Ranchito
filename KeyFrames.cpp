#include <iostream>
#include <cstdio>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"

// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();
void Animation();
void ActualizarToro();

// Window dimensions
//const GLuint WIDTH = 800, HEIGHT = 600;
const GLuint WIDTH = 2024, HEIGHT = 1080;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(0.0f, 2.0f, 10.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
bool active;

// Positions of the point lights
glm::vec3 pointLightPositions[] = {
	glm::vec3(0.0f,2.0f, 0.0f),
	glm::vec3(0.0f,0.0f, 0.0f),
	glm::vec3(0.0f,0.0f, 0.0f),
	glm::vec3(0.0f,0.0f, 0.0f)
};

float vertices[] = {
	 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

glm::vec3 Light1 = glm::vec3(0);

// ==========================================
// VARIABLES DE ANIMACIÓN
// ==========================================
float rotPFuera = 0.0f;
float rotPDentro = 0.0f;
float rotAbeja = 0.0f;

float caballoPosX = 0.0f, caballoPosY = 0.0f, caballoPosZ = 0.0f;
float vacaPosX = 0.0f, vacaPosY = 0.0f, vacaPosZ = 0.0f;
float cerdoPosX = 0.0f, cerdoPosY = 0.0f, cerdoPosZ = 0.0f;


// Variables de animación para el molino
float rotAspas = 0.0f;           // Girará infinitamente
float rotPuertaMolino = 0.0f;   


// Variables para la animación compleja del tractor
float avanceTractor = 0.0f;       // Distancia que recorre el tractor
float rotLlantasTractor = 0.0f;   // Ángulo de giro de las llantas
float anguloGiroDireccion = 0.0f; // Ángulo del volante
float anguloTractor = 0.0f;       // Rumbo del tractor (grados, giro sobre Y): hacia dónde apunta y avanza

// Posición del tractor en el mundo. Se va acumulando paso a paso con T / Y
const float TRACTOR_EJE_TRAS_Z = 1.2f;             // z local del eje trasero: el chasis gira alrededor de él
float tractorPosX = -12.0f;                        // el chasis arranca donde siempre:
float tractorPosZ = 5.0f + TRACTOR_EJE_TRAS_Z;     // (-12, 0, 5) con el rumbo en 0


// Variables para la animación de la puerta de la cochera
float alturaPuertaCochera = 0.0f; // Altura para deslizar la puerta hacia arriba


// ==========================================
// TORO (jerarquía con pivotes)
// Cada pieza del toro (cabeza y patas) se exporta con sus vértices en coordenadas LOCALES: centrada en su propio origen (el cuello o la cadera).
// Por eso se coloca con T(origen) * R, sin T(-origen).
// El frente del toro es -Z.
// ==========================================
const bool TORO_OBJ_LOCAL = true;
const glm::vec3 PIVOTE_CUELLO = glm::vec3(0.00f, 1.40f, -0.95f);
const glm::vec3 PIVOTE_DEL_IZQ = glm::vec3(-0.42f, 0.95f, -0.55f);
const glm::vec3 PIVOTE_DEL_DER = glm::vec3(0.42f, 0.95f, -0.55f);
const glm::vec3 PIVOTE_TRAS_IZQ = glm::vec3(-0.40f, 0.95f, 0.75f);
const glm::vec3 PIVOTE_TRAS_DER = glm::vec3(0.40f, 0.95f, 0.75f);

const float TORO_ESCALA = 1.0f;     // sube/baja para ajustar el tamaño en el rancho

float toroPosX = 5.0f, toroPosZ = 5.0f;   // posición en el rancho
float toroYaw = 45.0f;                    // rumbo (grados, giro sobre Y)
float toroFase = 0.0f;                    // fase del ciclo de marcha (radianes)
float toroMarcha = 0.0f;                  // 0 = parado, 1 = caminando (suavizado)
float toroCabezaYaw = 0.0f;               // giro de la cabeza (automático)
float toroCabezaPitch = 0.0f;             // cabeceo de la cabeza (automático)


// ==========================================
// SISTEMA DE KEYFRAMES
// ==========================================
// Lista de TODAS las variables que se animan. La tecla K guarda su valor actual
// como un keyframe y la tecla L reproduce la animación interpolando de umn keyframe al siguiente.

float* varsAnim[] = {
	// Puertas del rancho (teclas 1 2 3 4)
	&rotPFuera, &rotPDentro,
	// Animales (flechas para el caballo)
	&caballoPosX, &caballoPosY, &caballoPosZ,
	&vacaPosX, &vacaPosY, &vacaPosZ,
	&cerdoPosX, &cerdoPosY, &cerdoPosZ,
	// Molino: aspas (viento) y puertas (M abre, N cierra)
	&rotAspas, &rotPuertaMolino,
	// Tractor: dirección (U / I) y avance (T / Y): odómetro, llantas, volante, rumbo y posición
	&avanceTractor, &rotLlantasTractor, &anguloGiroDireccion, &anguloTractor,
	&tractorPosX, &tractorPosZ,
	// Cochera: altura de la puerta (O abre, P cierra)
	&alturaPuertaCochera,
	// Toro (Z X C V): posición, rumbo, fase de la marcha (mueve las patas) y cabeza
	&toroPosX, &toroPosZ, &toroYaw, &toroFase, &toroCabezaYaw, &toroCabezaPitch
};
const int N_VARS = (int)(sizeof(varsAnim) / sizeof(varsAnim[0]));

#define MAX_FRAMES 30
struct FRAME { float v[N_VARS]; };   // valor de cada variable de la lista en ese keyframe

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;      // cuántos keyframes hay guardados
bool play = false;       // true mientras se reproduce la animación
int playIndex = 0;       // tramo actual: de KeyFrame[playIndex] a KeyFrame[playIndex + 1]
float tTramo = 0.0f;     // avance dentro del tramo actual (0 a 1)

const float DURACION_TRAMO = 3.0f;        // segundos que tarda cada tramo entre dos keyframes
const bool SUAVIZAR_KEYFRAMES = false;    // false: lerp puro (velocidad constante); true: arranca y frena suave
const bool CABEZA_POR_KEYFRAMES = false;  // false: la cabeza del toro sigue moviéndose sola

void saveFrame(void)
{
	if (FrameIndex >= MAX_FRAMES) { printf("Ya no caben mas keyframes (maximo %d)\n", MAX_FRAMES); return; }
	for (int i = 0; i < N_VARS; i++) KeyFrame[FrameIndex].v[i] = *varsAnim[i];
	FrameIndex++;
	printf("KeyFrame %d guardado\n", FrameIndex);
}

// Pone todas las variables animadas exactamente en los valores de un keyframe
void aplicarFrame(int k)
{
	for (int i = 0; i < N_VARS; i++) *varsAnim[i] = KeyFrame[k].v[i];
}

// Posición de una variable dentro de la lista (sirve para leer su valor en un keyframe)
int idxVar(const float* p)
{
	for (int i = 0; i < N_VARS; i++) if (varsAnim[i] == p) return i;
	return 0;
}

// Regresa todo al primer keyframe antes de reproducir
void resetElements(void)
{
	aplicarFrame(0);
	toroMarcha = 0.0f;
}

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

// Coloca una pieza del toro en su articulación 'origen' y la gira con 'rot'.
// Con vértices locales (lo normal aquí): base * T(origen) * R.
// Con vértices en coordenadas de mundo: base * T(origen) * R * T(-origen).
glm::mat4 PiezaToro(const glm::mat4& base, const glm::vec3& origen, const glm::mat4& rot)
{
	glm::mat4 m = glm::translate(base, origen) * rot;
	if (!TORO_OBJ_LOCAL) m = glm::translate(m, -origen);
	return m;
}

// Rotación de 'grados' sobre el eje X (péndulo de las patas; + = hacia adelante)
glm::mat4 RotX(float grados)
{
	return glm::rotate(glm::mat4(1.0f), glm::radians(grados), glm::vec3(1.0f, 0.0f, 0.0f));
}

// Mueve el tractor 'ds' unidades (ds < 0 = adelante con T, ds > 0 = reversa con Y).
// La posición se acumula paso a paso en la dirección del rumbo (seno y coseno) y el rumbo cambia en porporción al ángulo del volante.
void MoverTractor(float ds)
{
	tractorPosX += sin(glm::radians(anguloTractor)) * ds;
	tractorPosZ += cos(glm::radians(anguloTractor)) * ds;
	avanceTractor += ds;
	rotLlantasTractor += 100.0f * ds;                    // 10 grados de llanta por cada 0.1 de avance
	anguloTractor -= anguloGiroDireccion * 0.15f * ds;   // volante a la izquierda (+) = el rumbo aumenta al avanzar
}

int main()
{
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Animacion Rancho", nullptr, nullptr);
	if (nullptr == window) return EXIT_FAILURE;

	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);

	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit()) return EXIT_FAILURE;

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");
	Shader lampShader("Shader/lamp.vs", "Shader/lamp.frag");

	// Carga de modelos
	Model piso((char*)"Models/piso.obj");
	Model RanchoNuevo2((char*)"Models/RanchoNuevo2.obj");
	Model vallas((char*)"Models/vallas.obj");
	//Model PuertasFueraRanchoNuevas((char*)"Models/PuertasFueraRanchoNuevas.obj");
	Model PuertasCentralesDentro((char*)"Models/PuertasCentralesDentro.obj");
	Model caballo((char*)"Models/caballo.obj");
	Model vaca((char*)"Models/vaca.obj");
	Model cerdo((char*)"Models/cerdo.obj");
	Model abeja((char*)"Models/abeja.obj");

	// Carga de los 4 objetos del molino
	Model Molino_Base((char*)"Models/Molino_Base3.obj");
	Model Molino_Aspas((char*)"Models/MolinoAspas.obj");
	Model Molino_Puerta_Izq((char*)"Models/Molino_Puerta_Izq.obj");
	Model Molino_Puerta_Der((char*)"Models/Molino_Puerta_Der.obj");

	// Cargar modelos del tractor
	Model Tractor_Cuerpo((char*)"Models/Tractor_Cuerpo.obj");
	Model Tractor_Rueda_Tras_Izq((char*)"Models/Tractor_Rueda_Tras_Izq.obj");
	Model Tractor_Rueda_Tras_Der((char*)"Models/Tractor_Rueda_Tras_Der.obj");
	Model Tractor_Rueda_Del_Izq((char*)"Models/Tractor_Rueda_Del_Izq.obj");
	Model Tractor_Rueda_Del_Der((char*)"Models/Tractor_Rueda_Del_Der.obj");

	// Cargar modelos de la cochera
	Model Cochera_Estructura((char*)"Models/Cochera_Estructura.obj");
	Model Cochera_Puerta((char*)"Models/Cochera_Puerta.obj");

	// Cargar los 6 modelos del toro
	Model Toro_Cuerpo((char*)"Models/Toro_Cuerpo.obj");
	Model Toro_Cabeza((char*)"Models/Toro_Cabeza.obj");
	Model Toro_PataDelIzq((char*)"Models/Toro_Pata_DelIzq.obj");
	Model Toro_PataDelDer((char*)"Models/Toro_Pata_DelDer.obj");
	Model Toro_PataTrasIzq((char*)"Models/Toro_Pata_TrasIzq.obj");
	Model Toro_PataTrasDer((char*)"Models/Toro_Pata_TrasDer.obj");

	//Cargar modelo de la cerca del rancho (tramo)
	Model Cerca_Tramo((char*)"Models/Cerca_Tramo.obj");


	printf("KEYFRAMES:  K = guardar keyframe  |  L = reproducir / detener  |  B = borrar todos\n");

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	lightingShader.Use();
	glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.difuse"), 0);
	glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.specular"), 1);

	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);

	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();
		DoMovement();
		Animation();
		ActualizarToro();

		glClearColor(0.53f, 0.81f, 0.92f, 1.0f); // Azul cielo (SkyBlue)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		lightingShader.Use();

		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.6f, 0.6f, 0.6f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.6f, 0.6f, 0.6f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.3f, 0.3f, 0.3f);

		glm::vec3 lightColor;
		lightColor.x = abs(sin(glfwGetTime() * Light1.x));
		lightColor.y = abs(sin(glfwGetTime() * Light1.y));
		lightColor.z = sin(glfwGetTime() * Light1.z);

		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 1.0f, 0.2f, 0.2f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.045f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.075f);

		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.2f, 0.2f, 0.8f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.2f, 0.2f, 0.8f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.3f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.7f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.0f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(18.0f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 5.0f);

		glm::mat4 view = camera.GetViewMatrix();
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glm::mat4 model(1.0f);

		// ========================================================
		// 1. DIBUJAR PISO 
		// ========================================================
		glUniform1i(glGetUniformLocation(lightingShader.Program, "uUseColorOnly"), GL_FALSE);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.3f, 0.0f));
		model = glm::scale(model, glm::vec3(50.0f, 1.0f, 50.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		piso.Draw(lightingShader);

		// ========================================================
		// 2. DIBUJAR RANCHO NUEVO Y VALLAS 
		// ========================================================
		glUniform1i(glGetUniformLocation(lightingShader.Program, "uUseColorOnly"), GL_TRUE);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.3f, -3.8f, -6.8f));
		model = glm::scale(model, glm::vec3(5.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		RanchoNuevo2.Draw(lightingShader);

		model = glm::mat4(1.0f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		vallas.Draw(lightingShader);

		//// ========================================================
		//// 3. DIBUJAR BLOQUE DE PUERTAS EXTERIORES (Con pivote desplazado)
		//// ========================================================
		//model = glm::mat4(1.0f);
		//// En lugar de rotar, sumamos "rotPFuera" al eje X para que se deslice hacia los lados.
		//// (Si ves que se deslizan hacia adelante/atrás en vez de a los lados, cambia "+ rotPFuera" al eje Z, es decir: -6.8f + rotPFuera)
		//model = glm::translate(model, glm::vec3(-0.3f + rotPFuera, -3.8f, -6.8f));
		//model = glm::scale(model, glm::vec3(5.3f)); // Escala numérica directa
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//PuertasFueraRanchoNuevas.Draw(lightingShader);

		// ========================================================
		// 4. DIBUJAR BLOQUE DE PUERTAS INTERIORES
		// ========================================================
		model = glm::mat4(1.0f);
		// Sumamos "rotPDentro" al eje X para que las de adentro también se deslicen.
		model = glm::translate(model, glm::vec3(rotPDentro, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PuertasCentralesDentro.Draw(lightingShader);


		// ========================================================
		// 5. DIBUJAR ANIMALES
		// ========================================================
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(caballoPosX, caballoPosY, caballoPosZ));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		caballo.Draw(lightingShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(vacaPosX, vacaPosY, vacaPosZ));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		vaca.Draw(lightingShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(cerdoPosX, cerdoPosY, cerdoPosZ));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		cerdo.Draw(lightingShader);

		// ========================================================
		// 6. DIBUJAR ABEJA 
		// ========================================================
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 1);

		rotAbeja += 0.2f;
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 5.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotAbeja), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		abeja.Draw(lightingShader);

		glDisable(GL_BLEND);
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);


		// ========================================================
		// RENDERIZADO DEL MOLINO DE VIENTO (4 Objetos + Animaciones)
		// ========================================================

		// 1. Posición general del molino en tu rancho
		glm::vec3 posMolino = glm::vec3(15.0f, 0.0f, 1.0f); // Cambia esto para reubicarlo donde quieras

		// 2. DIBUJAR BASE
		model = glm::mat4(1.0f);
		model = glm::translate(model, posMolino);
		// model = glm::scale(model, glm::vec3(1.0f)); // Descomenta y ajusta si lo ves muy grande/chico
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Molino_Base.Draw(lightingShader);

		// 3. DIBUJAR Y ANIMAR ASPAS (Animación Básica 1: Rotación Continua)
		// El viento hace girar las aspas; al reproducir keyframes manda la animación.
		// Sin recortar a 360°, así un keyframe a otro siempre gira hacia adelante.
		if (!play) rotAspas += 0.5f;

		model = glm::mat4(1.0f);
		model = glm::translate(model, posMolino);
		model = glm::translate(model, glm::vec3(0.0f, 4.4f, 2.3f)); // Sube las aspas al techo (Coordenadas de Blender convertidas a OpenGL)
		model = glm::rotate(model, glm::radians(rotAspas), glm::vec3(0.0f, 0.0f, 1.0f)); // Gira sobre el eje Z (Frontal)
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Molino_Aspas.Draw(lightingShader);

		// 4. DIBUJAR Y ANIMAR PUERTA IZQUIERDA (Animación Básica 2: Bisagra)
		model = glm::mat4(1.0f);
		model = glm::translate(model, posMolino);
		model = glm::translate(model, glm::vec3(-0.5f, 0.0f, 1.82f)); // Offset de la bisagra izquierda
		model = glm::rotate(model, glm::radians(rotPuertaMolino), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Molino_Puerta_Izq.Draw(lightingShader);

		// 5. DIBUJAR Y ANIMAR PUERTA DERECHA (Bisagra Inversa)
		model = glm::mat4(1.0f);
		model = glm::translate(model, posMolino);
		model = glm::translate(model, glm::vec3(0.5f, 0.0f, 1.82f)); // Offset de la bisagra derecha
		model = glm::rotate(model, glm::radians(-rotPuertaMolino), glm::vec3(0.0f, 1.0f, 0.0f)); // Nota el signo negativo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Molino_Puerta_Der.Draw(lightingShader);



		// ========================================================
		// RENDERIZADO DEL TRACTOR 
		// ========================================================

		// 1. y 2. MATRIZ BASE PADRE (traslada y ROTA todo el chasis hacia donde apunta).
		// (tractorPosX, tractorPosZ) es el punto del eje trasero: se traslada ahí, se gira
		// con el rumbo y el modelo se corre hacia atrás para que su eje trasero quede en ese punto.
		glm::mat4 tractorBase = glm::mat4(1.0f);
		tractorBase = glm::translate(tractorBase, glm::vec3(tractorPosX, 0.0f, tractorPosZ));
		tractorBase = glm::rotate(tractorBase, glm::radians(anguloTractor), glm::vec3(0.0f, 1.0f, 0.0f));
		tractorBase = glm::translate(tractorBase, glm::vec3(0.0f, 0.0f, -TRACTOR_EJE_TRAS_Z));

		// 3. DIBUJAR CUERPO DEL TRACTOR
		model = tractorBase;
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Tractor_Cuerpo.Draw(lightingShader);

		// 4. DIBUJAR RUEDA TRASERA IZQUIERDA 
		model = tractorBase;
		model = glm::translate(model, glm::vec3(-0.9f, 0.7f, 1.2f)); // X: Izquierda (-), Y: Altura, Z: Atrás (+)
		model = glm::rotate(model, glm::radians(rotLlantasTractor), glm::vec3(1.0f, 0.0f, 0.0f)); // Rota sobre X
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Tractor_Rueda_Tras_Izq.Draw(lightingShader);

		// 5. DIBUJAR RUEDA TRASERA DERECHA
		model = tractorBase;
		model = glm::translate(model, glm::vec3(0.9f, 0.7f, 1.2f)); // X: Derecha (+), Y: Altura, Z: Atrás (+)
		model = glm::rotate(model, glm::radians(rotLlantasTractor), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Tractor_Rueda_Tras_Der.Draw(lightingShader);

		// 6. DIBUJAR RUEDA DELANTERA IZQUIERDA (Con dirección y rodamiento)
		model = tractorBase;
		model = glm::translate(model, glm::vec3(-0.7f, 0.4f, -1.3f));
		model = glm::rotate(model, glm::radians(anguloGiroDireccion), glm::vec3(0.0f, 1.0f, 0.0f)); // 1. Gira para dar vuelta (Eje Y)
		model = glm::rotate(model, glm::radians(rotLlantasTractor), glm::vec3(1.0f, 0.0f, 0.0f));   // 2. Rueda hacia adelante/atrás (Eje X)
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Tractor_Rueda_Del_Izq.Draw(lightingShader);

		// 7. DIBUJAR RUEDA DELANTERA DERECHA (Con dirección y rodamiento)
		model = tractorBase;
		model = glm::translate(model, glm::vec3(0.7f, 0.4f, -1.3f));
		model = glm::rotate(model, glm::radians(anguloGiroDireccion), glm::vec3(0.0f, 1.0f, 0.0f)); // 1. Gira para dar vuelta (Eje Y)
		model = glm::rotate(model, glm::radians(rotLlantasTractor), glm::vec3(1.0f, 0.0f, 0.0f));   // 2. Rueda hacia adelante/atrás (Eje X)
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Tractor_Rueda_Del_Der.Draw(lightingShader);




		// ========================================================
		// RENDERIZADO DE LA COCHERA (Animación Sencilla)
		// ========================================================
		glm::vec3 posCochera = glm::vec3(-12.0f, 0.0f, 5.0f); // Posición al lado de tu rancho

		// 1. Estructura fija
		model = glm::mat4(1.0f);
		model = glm::translate(model, posCochera);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Cochera_Estructura.Draw(lightingShader);

		// 2. Puerta deslizable hacia arriba
		model = glm::mat4(1.0f);
		model = glm::translate(model, posCochera);
		model = glm::translate(model, glm::vec3(0.0f, alturaPuertaCochera, 3.0f)); 
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Cochera_Puerta.Draw(lightingShader);




		// ========================================================
		// RENDERIZADO DEL TORO (jerarquía + pivotes)
		// ========================================================
		glUniform1i(glGetUniformLocation(lightingShader.Program, "uUseColorOnly"), GL_TRUE);

		// Marcha en trote diagonal: pata delantera izq. + trasera der. avanzan juntas
		float s = sin(toroFase) * toroMarcha;
		float angDel = 24.0f * s;     // las delanteras balancean un poco más
		float angTras = 20.0f * s;

		// El cuerpo baja un poco cuando las patas están inclinadas (las patas miden 0.95
		// de la cadera al suelo), para que la pata más inclinada siga tocando el piso
		float angMax = fmax(fabs(angDel), fabs(angTras));
		float hundimiento = 0.95f * (1.0f - cos(glm::radians(angMax)));

		glm::mat4 toroBase = glm::mat4(1.0f);
		toroBase = glm::translate(toroBase, glm::vec3(toroPosX, -hundimiento, toroPosZ));
		toroBase = glm::rotate(toroBase, glm::radians(toroYaw), glm::vec3(0.0f, 1.0f, 0.0f));
		toroBase = glm::scale(toroBase, glm::vec3(TORO_ESCALA));

		// Cuerpo (su origen es el (0,0,0) del toro: sin translate extra)
		model = toroBase;
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Toro_Cuerpo.Draw(lightingShader);

		// Cabeza: se coloca en la base del cuello y gira ahí (yaw sobre Y, cabeceo sobre X)
		glm::mat4 rotCabeza = glm::rotate(glm::mat4(1.0f), glm::radians(toroCabezaYaw), glm::vec3(0.0f, 1.0f, 0.0f))
			* glm::rotate(glm::mat4(1.0f), glm::radians(toroCabezaPitch), glm::vec3(1.0f, 0.0f, 0.0f));
		model = PiezaToro(toroBase, PIVOTE_CUELLO, rotCabeza);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Toro_Cabeza.Draw(lightingShader);

		// Patas: cada una se coloca en su cadera/hombro y oscila como péndulo sobre X
		model = PiezaToro(toroBase, PIVOTE_DEL_IZQ, RotX(angDel));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Toro_PataDelIzq.Draw(lightingShader);

		model = PiezaToro(toroBase, PIVOTE_DEL_DER, RotX(-angDel));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Toro_PataDelDer.Draw(lightingShader);

		model = PiezaToro(toroBase, PIVOTE_TRAS_IZQ, RotX(-angTras));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Toro_PataTrasIzq.Draw(lightingShader);

		model = PiezaToro(toroBase, PIVOTE_TRAS_DER, RotX(angTras));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Toro_PataTrasDer.Draw(lightingShader);


		// ========================================================
		// RENDERIZADO DEL PERÍMETRO DE CERCAS 
		// ========================================================
		glUniform1i(glGetUniformLocation(lightingShader.Program, "uUseColorOnly"), GL_FALSE);

		// Cada tramo de cerca mide aproximadamente 2.0 unidades de largo
		float longitudTramo = 2.0f;

		// Límites del rancho
		float minX = -45.0f, maxX = 45.0f;
		float minZ = -45.0f, maxZ = 45.0f;

		// 1. Pared Frontal (Z fijo en maxZ)
		for (float x = minX; x <= maxX; x += longitudTramo) {
			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(x, 0.0f, maxZ));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			Cerca_Tramo.Draw(lightingShader);
		}

		// 2. Pared Trasera (Z fijo en minZ)
		for (float x = minX; x <= maxX; x += longitudTramo) {
			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(x, 0.0f, minZ));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			Cerca_Tramo.Draw(lightingShader);
		}

		// 3. Pared Izquierda (X fijo en minX)
		for (float z = minZ; z <= maxZ; z += longitudTramo) {
			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(minX, 0.0f, z));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			Cerca_Tramo.Draw(lightingShader);
		}

		// 4. Pared Derecha (X fijo en maxX)
		for (float z = minZ; z <= maxZ; z += longitudTramo) {
			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(maxX, 0.0f, z));
			model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			Cerca_Tramo.Draw(lightingShader);
		}






		// ========================================================
		// 7. DIBUJAR FUENTE DE LUZ
		// ========================================================
		lampShader.Use();
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		//projLoc = glGetUniformLocation(lampShader.Program, "projection"); //los cubos

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		for (GLuint i = 0; i < 4; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

void DoMovement()
{
	// Controles manuales (se desactivan mientras se reproducen los keyframes)
	if (!play)
	{
		if (keys[GLFW_KEY_1]) rotPFuera += 0.02f;
		if (keys[GLFW_KEY_2]) rotPFuera -= 0.02f;
		if (keys[GLFW_KEY_3]) rotPDentro += 0.02f;
		if (keys[GLFW_KEY_4]) rotPDentro -= 0.02f;

		if (keys[GLFW_KEY_RIGHT]) caballoPosZ -= 0.005f;
		if (keys[GLFW_KEY_LEFT]) caballoPosZ += 0.005f;
		if (keys[GLFW_KEY_DOWN]) caballoPosX -= 0.005f;
		if (keys[GLFW_KEY_UP]) caballoPosX += 0.005f;
	}

	if (keys[GLFW_KEY_W]) camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S]) camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A]) camera.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D]) camera.ProcessKeyboard(RIGHT, deltaTime);
}

// ============================================================
// TORO: movimiento y animación (se llama cada frame)
// Controles: X = avanzar | Z = retroceder | C = girar izq. | V = girar der.
// La cabeza se mueve sola. Las patas se mueven en trote diagonal.
// ============================================================
void ActualizarToro()
{
	const float VEL = 1.2f;              // m/s al caminar
	const float GIRO = 70.0f;            // grados/s al girar
	const float FASE_POR_METRO = 4.0f;   // rad por metro recorrido: evita que las patas "patinen"

	if (!play)
	{
		// --- Entrada de teclado ---
		float avance = 0.0f;
		if (keys[GLFW_KEY_X]) avance += VEL;           // adelante
		if (keys[GLFW_KEY_Z]) avance -= VEL * 0.6f;    // atrás 

		float giro = 0.0f;
		if (keys[GLFW_KEY_C]) giro += GIRO;            // izquierda
		if (keys[GLFW_KEY_V]) giro -= GIRO;            // derecha
		if (avance == 0.0f && giro != 0.0f) avance = VEL * 0.4f; // gira dando pasos, no patina

		// --- Movimiento del cuerpo (el frente del toro es -Z local) ---
		float dist = avance * deltaTime;
		float yawRad = glm::radians(toroYaw);
		toroPosX += -sin(yawRad) * dist;
		toroPosZ += -cos(yawRad) * dist;
		toroYaw += giro * deltaTime;

		// La fase avanza según la distancia recorrida (si retrocede, el ciclo se invierte)
		toroFase += dist * FASE_POR_METRO;

		// Las patas vuelven suavemente a su posición neutra al detenerse
		float objetivo = (avance != 0.0f) ? 1.0f : 0.0f;
		toroMarcha += (objetivo - toroMarcha) * glm::min(1.0f, 8.0f * deltaTime);
	}
	else
	{
		// --- Reproduciendo keyframes ---
		// La posición, el rumbo y la fase de la marcha ya vienen interpolados (Animation()).
		// Aquí solo se decide si las patas caminan en este tramo; al arrancar y frenar
		// (inicio y final del tramo) la marcha se apaga suavemente, como un paso real.
		const FRAME& a = KeyFrame[playIndex];
		const FRAME& b = KeyFrame[playIndex + 1];
		float dFase = fabs(b.v[idxVar(&toroFase)] - a.v[idxVar(&toroFase)]);
		float dPos = fabs(b.v[idxVar(&toroPosX)] - a.v[idxVar(&toroPosX)])
			+ fabs(b.v[idxVar(&toroPosZ)] - a.v[idxVar(&toroPosZ)]);
		bool moviendo = (dFase > 0.01f) || (dPos > 0.01f);
		float ritmo = SUAVIZAR_KEYFRAMES ? glm::min(1.0f, 6.0f * tTramo * (1.0f - tTramo)) : 1.0f;
		float objetivo = moviendo ? ritmo : 0.0f;
		toroMarcha += (objetivo - toroMarcha) * glm::min(1.0f, 8.0f * deltaTime);
	}

	// Cabeza: movimiento AUTOMÁTICO (mira a los lados y cabecea suave)
	// (con CABEZA_POR_KEYFRAMES = true, al reproducir obedece a los keyframes)
	if (!(play && CABEZA_POR_KEYFRAMES))
	{
		float t = (float)glfwGetTime();
		toroCabezaYaw = sin(t * 0.9f) * 22.0f + sin(t * 2.3f) * 4.0f;
		toroCabezaPitch = sin(t * 1.4f) * 6.0f - 3.0f + sin(toroFase * 2.0f) * 3.0f * toroMarcha;
	}
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// ========================================================
	// KEYFRAMES:  K = guardar  |  L = reproducir / detener  |  B = borrar todos
	// Se procesan al PRESIONAR la tecla
	// ========================================================
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_K && !play) saveFrame();

		if (key == GLFW_KEY_L)
		{
			if (play)
			{
				play = false;
				printf("Animacion detenida\n");
			}
			else if (FrameIndex > 1)
			{
				resetElements();
				play = true;
				playIndex = 0;
				tTramo = 0.0f;
				printf("Reproduciendo %d keyframes\n", FrameIndex);
			}
			else printf("Necesitas al menos 2 keyframes (tecla K)\n");
		}

		if (key == GLFW_KEY_B && !play)
		{
			FrameIndex = 0;
			printf("Keyframes borrados\n");
		}
	}

	// Durante la reproducción los controles manuales de las animaciones se desactivan
	bool manual = !play;


	// ========================================================
	// CONTROLES DEL MOLINO
	// ========================================================

	// Abrir puertas con la letra M
	if (manual && glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
		rotPuertaMolino += 1.5f; // Velocidad de apertura
		if (rotPuertaMolino > 120.0f) {
			rotPuertaMolino = 120.0f; // Tope para que no atraviesen la pared
		}
	}

	// Cerrar puertas con la letra N
	if (manual && glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
		rotPuertaMolino -= 1.5f; // Velocidad de cierre
		if (rotPuertaMolino < 0.0f) {
			rotPuertaMolino = 0.0f; // Tope para que queden bien cerradas
		}
	}

	// ========================================================
	// CONTROLES DEL TRACTOR (ANIMACIÓN COMPLEJA)
	// ========================================================

	// Girar dirección con U y I
	if (manual && glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
		anguloGiroDireccion += 2.0f;
		if (anguloGiroDireccion > 35.0f) anguloGiroDireccion = 35.0f;
	}
	if (manual && glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
		anguloGiroDireccion -= 2.0f;
		if (anguloGiroDireccion < -35.0f) anguloGiroDireccion = -35.0f;
	}

	// Avanzar con T y retroceder con Y 
	if (manual && glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
		MoverTractor(-0.1f);
	}
	if (manual && glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
		MoverTractor(0.1f);
	}


	// ========================================================
	// CONTROLES DE LA COCHERA (ANIMACIÓN BÁSICA)
	// ========================================================

	// Abrir cochera con la letra O
	if (manual && glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
		alturaPuertaCochera += 0.05f;
		if (alturaPuertaCochera > 2.5f) alturaPuertaCochera = 2.5f; // Tope de apertura
	}
	// Cerrar cochera con la letra P
	if (manual && glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
		alturaPuertaCochera -= 0.05f;
		if (alturaPuertaCochera < 0.0f) alturaPuertaCochera = 0.0f; // Tope cerrado
	}


	




	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS) keys[key] = true;
		else if (action == GLFW_RELEASE) keys[key] = false;
	}

	if (keys[GLFW_KEY_SPACE])
	{
		active = !active;
		if (active) Light1 = glm::vec3(0.2f, 0.8f, 1.0f);
		else Light1 = glm::vec3(0);
	}
}

// Reproduce los keyframes: en cada cuadro avanza dentro del tramo actual y
// pone TODAS las variables de la lista entre el keyframe de salida y el de llegada.
// Depende del tiempo (deltaTime), no de los FPS.
void Animation()
{
	if (!play) return;

	tTramo += deltaTime / DURACION_TRAMO;
	if (tTramo >= 1.0f)
	{
		// Llegó al siguiente keyframe: queda exactamente en sus valores
		playIndex++;
		aplicarFrame(playIndex);
		tTramo = 0.0f;
		if (playIndex >= FrameIndex - 1)   // era el último
		{
			printf("Termina animacion\n");
			play = false;
			playIndex = 0;
		}
		return;
	}

	// Interpolación lineal (lerp) de TODAS las variables de la lista, incluidas la
	// posición (x, z), el rumbo, el volante y las llantas del tractor
	float e = SUAVIZAR_KEYFRAMES ? tTramo * tTramo * (3.0f - 2.0f * tTramo) : tTramo;
	for (int i = 0; i < N_VARS; i++)
	{
		float a = KeyFrame[playIndex].v[i];
		float b = KeyFrame[playIndex + 1].v[i];
		*varsAnim[i] = a + (b - a) * e;
	}
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}
	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;
	lastX = xPos;
	lastY = yPos;
	camera.ProcessMouseMovement(xOffset, yOffset);
}