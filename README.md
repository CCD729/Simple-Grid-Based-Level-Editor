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
Arrow Left [��] /Right [��] - Change tile selection  
S - Save current level to txt file  
L - Load a level from txt file   
F2 - Save a screenshot of current level to png file (in the same folder with the editor)

Save & Load
===========
When you try to save or load level from/to txt file, you will be prompted to enter a path/file in console as the target file.  
Example:  
`level.txt` or `Saves/level.txt`  
Note that while saving, this program could not create a directory for you if you try to save the file to a new folder that does not exist.  


��л��ʹ��������׹ؿ��༭����

��������
===========
����������ʱ������̨����Ҫ��������һ���ļ�·���Լ�����ѡ��Ĳ��ʡ���·���У������ʹ�� "\" �� "\\" ���滻 "/" �Ա������ȷʶ��  
������  
`Tileset/Platformer-Tileset-70x70.png`  
�����ѡ��ͬһ���ļ����е���һ�������ļ���������ϲ���Ĳ����ļ���  
֮���㽫��Ҫ�����뵥�����ӵĿ���볤�ȣ����أ��������Ϸ����������ļ����˴�Ӧ����70��70��  
�ɹ���������ļ��󣬴��ڽ��Զ�������ѡ��Ĳ����ļ��뵥�����ӳߴ������С���γ�һ��12x10�����������ڿ��Կ�ʼ�༭�ؿ��ˡ�  

�ȼ�
===========
������ - �ڵ�ǰ���ӷ���һƬͼ��  
����Ҽ� - ������ǰλ�õ�ͼ��  
���ҷ���� [��] [��] - �ı䵱ǰͼ��ѡ��  
S - ���浱ǰ�ؿ���txt�ļ�  
L - ��txt�ļ����عؿ����༭��  
F2 - ���浱ǰ�ؿ���ͼ��png�ļ����뱾����λ��ͬһ�ļ��У�

���� & ����
===========
������ͼͨ��txt�ļ�����/���عؿ�ʱ������̨����Ҫ��������һ���ļ�·����ΪĿ���ļ���  
������  
`level.txt` �� `Saves/level.txt`  
��ע�⵱�����ļ�ʱ���������޷�������Ŀ¼�����������ѡ����һ�������ڵ�·���������򽫲��ᴴ�����ļ��У�Ҳ���ᱣ��ؿ���
