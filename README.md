# 🤠 Proyecto Final: Animación y Modelado 3D de un Rancho

Simulación interactiva en 3D de un entorno de rancho desarrollada como proyecto final para la materia de **Computación Gráfica** en la **Facultad de Ingeniería de la UNAM**.

## 🛠️ Tecnologías y Herramientas
* **Lenguaje:** C++
* **Motor Gráfico:** OpenGL
* **Librerías:** GLFW, GLEW, GLM, Assimp, STB Image / SOIL2
* **Modelado 3D:** Blender

## ✨ Características Principales
* **Entorno Ampliado y Delimitado:** Terreno texturizado de gran escala rodeado por un perímetro modular de cercas de madera.
* **Sistema de KeyFrames (Fotogramas Clave):** Animaciones automatizadas con interpolación lineal y control por teclado (`K` para guardar, `L` para reproducir, `B` para reiniciar).
* **Modelos Jerárquicos y Articulados:** 
  * **Toro Orgánico:** Jerarquía de matrices con pivotes en articulaciones para simular marcha en trote y movimiento natural de cabeza.
  * **Tractor Completo:** Chasis y ruedas independientes con animación integrada.
  * **Molino de Viento:** Aspas giratorias por viento y puertas con bisagras.
* **Iluminación Avanzada:** Luces direccionales, luces de posición (point lights) y efectos de transparencia (Blending) para la vegetación/abeja.

## 🎮 Controles de la Escena
* **W, A, S, D:** Movimiento libre de la cámara en el entorno.
* **Mouse:** Orientación de la vista.
* **K:** Guardar Keyframe actual.
* **L:** Reproducir / Detener animación por KeyFrames.
* **B:** Borrar todos los KeyFrames guardados.
* **1 y 2 / 3 y 4:** Apertura y cierre de puertas del rancho.
* **M y N:** Apertura y cierre de puertas del molino.
* **O y P:** Subir y bajar la puerta de la cochera.
* **Espacio:** Alternar iluminación de la escena.

## 👥 Integrantes
* Jiménez Vázquez Sergio Yahir (320159204)
* Nequis Sarabia Jorge Luis (320176993)

**Profesor:** Ing. Edén Espinoza Urzúa  
**Semestre:** 2027-1 | **Grupo:** 04  
Facultad de Ingeniería, UNAM.
