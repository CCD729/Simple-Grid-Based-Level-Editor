# Simple-Grid-Based-Level-Editor
GAME 230 Project 2. A simple grid-based level editor tool created with C++ and SFML that allows a user to load, draw, and save a level as well as export a screenshot of the level to share with friends.

Thank you for using this simple level editor!

Startup
===========
You will be prompted to enter a path/file in console to load the tileset you prefer. You may replace "\" with "/" or use double slash "\\" in the path for directories.  
Example:  
`Tileset/Platformer-Tileset-70x70.png`  
You may use another file in the same folder or add one if you like.  
Then you will be prompted to enter the width and height for the tile you choose (in pixels). For the given example you should input 70 for both width and height.  
After loading the tileset, the window will automatically resize to adapt a 12x10 grid according to your choice of tile size and you may begin editing.  

Hotkeys
===========
Left mouse button - Place a tile on the grid  
Right mouse button - Erase a tile  
Arrow Left [←] /Right [→] - Change tile selection  
S - Save current level to txt file  
L - Load a level from txt file   
F2 - Save a screenshot of current level to png file (in the same folder with the editor)

Save & Load
===========
When you try to save or load level from/to txt file, you will be prompted to enter a path/file in console as the target file.  
Example:  
`level.txt` or `Saves/level.txt`  
Note that while saving, this program could not create a directory for you if you try to save the file to a new folder that does not exist.  


感谢你使用这个简易关卡编辑器！

启动设置
===========
启动本程序时，控制台将会要求你输入一个文件路径以加载你选择的材质。在路径中，你可以使用 "\" 或 "\\" 来替换 "/" 以便程序正确识别。  
样例：  
`Tileset/Platformer-Tileset-70x70.png`  
你可以选择同一个文件夹中的另一个材质文件，或导入你喜爱的材质文件。  
之后你将被要求输入单个格子的宽度与长度（像素）。对于上方样例材质文件，此处应输入70与70。  
成功导入材质文件后，窗口将自动根据你选择的材质文件与单个格子尺寸适配大小，形成一个12x10的网格。你现在可以开始编辑关卡了。  

热键
===========
鼠标左键 - 在当前格子放置一片图块  
鼠标右键 - 擦除当前位置的图块  
左右方向键 [←] [→] - 改变当前图块选择  
S - 保存当前关卡至txt文件  
L - 从txt文件加载关卡至编辑器  
F2 - 保存当前关卡截图至png文件（与本程序位于同一文件夹）

保存 & 加载
===========
当你试图通过txt文件保存/加载关卡时，控制台将会要求你输入一个文件路径作为目标文件。  
样例：  
`level.txt` 或 `Saves/level.txt`  
请注意当保存文件时，本程序无法创建新目录，所以如果你选择了一个不存在的路径，本程序将不会创建新文件夹，也不会保存关卡。
