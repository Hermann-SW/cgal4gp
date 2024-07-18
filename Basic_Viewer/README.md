## Basic Viewer

See [prerequisites](#prerequisites) and [build](#build) section — work in progress ...


Below few PARI/GP commands
- determine convex hull of ```points``` (returns ```#vertices```, ```#edges```, ```#halfedges``` and ```#faces```)
- and then display that in CGAL Basic Viewer  
```
pi@raspberrypi5:~/qh $ gp -q BVcgal4.gp
? points=[[1, 0, 0], [2, -1, 0], [2, 0, -1], [3, 0, 0], [2, 1, 0], [2, 0, 1]];
? CGAL_convex_hull_3(points)
[6, 12, 24, 8]
? CGAL_draw()
Using OpenGL context 4.5 GL
```  
<img src="../res/Basic_Viewer.demo.anim.gif">


### prerequisites

Installed libcgal-dev is version 5.4 on most systems, and that has Qt related bugs not allowing to get CGAL Basic Viewer working. Just  
```
sudo apt remove libcgal-dev
```
and then download [CGAL-5.6.1.zip](https://github.com/CGAL/cgal/releases/download/v5.6.1/CGAL-5.6.1.zip). Unzip under ```$HOME``` and execute  
```
sudo ln -s $HOME/CGAL-5.6.1/include/CGAL /usr/include/CGAL
```
Finally execute these commands:  
```
echo "export CGAL_DIR=$HOME/CGAL-5.6.1" >> ~/.bashrc
source ~/.bashrc
```

#### detailed steps to install Qt

```
sudo apt install qtcreator qtbase5-dev qt5-qmake
```

Work in progress ...

### build

[really_clean](really_clean) does what it says, [build+run](build+run) as well.  
Unlike building in ```cgal4gp``` base directory, here ```cmake``` based build is needed (for the ```Qt``` stuff).

Work in progress ...

