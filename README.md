🐄 Proyecto Final: Animación y Modelado 3D de un Rancho

Repositorio del proyecto final para el Laboratorio de Computación Gráfica e Interacción Humano-Computadora de la Facultad de Ingeniería, UNAM (Semestre 2027-1).

Este proyecto consiste en una simulación interactiva en 3D de un rancho, desarrollada en C++ y OpenGL. Destaca por la implementación de transformaciones geométricas jerárquicas y un sistema de interpolación lineal mediante fotogramas clave (KeyFrames) para automatizar las animaciones de la escena.

✨ Características Principales

Modelado 3D (Assimp): Integración de modelos exportados desde Blender (Tractor, Molino, Cochera, Animales y Cercas perimetrales).

Transformaciones Jerárquicas: Animación articulada compleja. El toro cuenta con pivotes independientes para la cabeza y un sistema de péndulo para el movimiento de las cuatro patas durante la marcha.

Sistema de KeyFrames: Permite guardar estados de las variables de animación (posición, rotación) en tiempo real y reproducirlos de manera continua y fluida (interpolación lineal).

Iluminación y Texturizado: Implementación de luces de punto (Point Lights) direccionales y materiales texturizados utilizando SOIL2/STB_Image.

Cámara Libre: Navegación por la escena utilizando el teclado y el ratón.

🛠️ Tecnologías y Librerías

Lenguaje: C++

API Gráfica: OpenGL

Manejo de Ventanas y Entradas: GLFW

Carga de Extensiones Gráficas: GLEW

Matemáticas: GLM (OpenGL Mathematics)

Carga de Modelos 3D: Assimp (Open Asset Import Library)

Carga de Texturas: SOIL2 / STB_Image

🎮 Controles de la Escena

Cámara Sintética

W, A, S, D: Movimiento de la cámara (Adelante, Izquierda, Atrás, Derecha).

Ratón (Mouse): Orientación de la vista.

Sistema de KeyFrames (Animación Automática)

K: Guardar fotograma clave (Keyframe) actual.

L: Reproducir o detener la animación (interpola entre los fotogramas guardados).

B: Borrar todos los fotogramas guardados (Reset).

Controles Manuales (Disponibles cuando la animación está pausada)

Tractor: T (Avanzar), Y (Retroceder), U / I (Girar dirección).

Toro (Marcha articulada): X (Avanzar), Z (Retroceder), C / V (Girar izquierda/derecha).

Cochera: O (Subir puerta), P (Bajar puerta).

Molino: M (Abrir puertas), N (Cerrar puertas).

Puertas del Rancho: 1, 2, 3, 4.

👥 Autores

Jiménez Vázquez Sergio Yahir (No. Cuenta: 320159204)

Nequis Sarabia Jorge Luis (No. Cuenta: 320176993)
