Simple platform game to experiment with external level creation via TILED



Dependencies:

SFML
box2d



Build:

Well, as this project is somewhat experimental, building routine is tedious and some manual work is required :(

1. Download full SFML2.5.1
2. Build box2d. As it is downloaded as submodule, follow the instruction in box2d\\readme.md
3. Specify include an lib paths to installed files for SFML and box2d in project settings
4. Specify LD\_LIBRARY path to SFML/bin for execution, as it requires .dll (or copy all .dll in output directory)

![Demo](https://github.com/ArcasHH/SimplePlatformer/blob/e190ed6e4d4e1de0a6811cdc7f0ee5372f060265/PlatformerPreview.gif)
