# miniRT
Simple raytracing implementation


<img src="./Ray_Tracing_Illustration_First_Bounce.png" width="400" alt="Illumination equation">

*Image taken from Wikipedia*

## Theory
### Rendering equation
```math
L_{o}(x,\omega) = L_{e}(x,\omega )+\int_{\Omega }L_{i}(x,\omega)f_{r}(x,\omega, \omega )(\omega \cdot n) \, \mathrm{d} \omega
```
> This is the key academic/theoretical concept in rendering. It serves as the most abstract formal expression of the non-perceptual aspect of rendering. All more complete algorithms can be seen as solutions to particular formulations of this equation. 
Meaning: at a particular position and direction, the outgoing light ($L_o$) is the sum of the emitted light ($L_e$) and the reflected light. The reflected light being the sum of the incoming light ($L_i$) from all directions, multiplied by the surface reflection and incoming angle. By connecting outward light to inward light, via an interaction point, this equation stands for the whole 'light transport' – all the movement of light – in a scene.
*[Wikipedia](https://w.wiki/5sQd)*
