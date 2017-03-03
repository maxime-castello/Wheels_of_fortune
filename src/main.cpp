/*****************************************************************************\
 * TP CPE, 3ETI, TP synthese d'images
 * --------------
 *
 * Programme principal des appels OpenGL
\*****************************************************************************/



#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <unistd.h> 


#define GLEW_STATIC 1
#include <GL/glew.h>
#include <GL/glut.h> // GLUT/GLUT.H --> GL/glut.h

#include "glutils.hpp"

#include "mat4.hpp"
#include "vec3.hpp"
#include "vec2.hpp"
#include "triangle_index.hpp"
#include "vertex_opengl.hpp"
#include "image.hpp"
#include "mesh.hpp"

#include <stdio.h>
#include<string.h>
#include<stdlib.h>


/*****************************************************************************\
 * Variables globales
 *
 *
\*****************************************************************************/


//identifiant du shader 
GLuint shader_program_id;

//identifiants pour object 1
GLuint vbo_object_1=0;
GLuint vboi_object_1=0;
GLuint texture_id_object_1=0;
int nbr_triangle_object_1;

//identifiants pour object 2
GLuint vbo_object_2=0;
GLuint vboi_object_2=0;
GLuint texture_id_object_2=0;
int nbr_triangle_object_2;

//identifiants pour object 3
GLuint vbo_object_3=0;
GLuint vboi_object_3=0;
GLuint texture_id_object_3=0;
int nbr_triangle_object_3;
const int nbr_tree=22;

//identifiants pour object 4 
GLuint vbo_object_4=0;
GLuint vboi_object_4=0;
GLuint texture_id_object_4=0;
int nbr_triangle_object_4;

//identifiants pour object 5
GLuint vbo_object_5=0;
GLuint vboi_object_5=0;
GLuint texture_id_object_5=0;
int nbr_triangle_object_5;

//identifiants pour object 6
GLuint vbo_object_6=0;
GLuint vboi_object_6=0;
GLuint texture_id_object_6=0;
int nbr_triangle_object_6;

//identifiants pour object 7
GLuint vbo_object_7=0;
GLuint vboi_object_7=0;
GLuint texture_id_object_7=0;
int nbr_triangle_object_7;

//identifiants pour object 8
GLuint vbo_object_8=0;
GLuint vboi_object_8=0;
GLuint texture_id_object_8=0;
int nbr_triangle_object_8;

//identifiants pour object 9 (pièce)
GLuint vbo_object_9=0;
GLuint vboi_object_9=0;
GLuint texture_id_object_9=0;
int nbr_triangle_object_9;

//identifiants pour object 10(ennemi)
GLuint vbo_object_10=0;
GLuint vboi_object_10=0;
GLuint texture_id_object_10=0;
int nbr_triangle_object_10;

bool avant;
bool arriere;
bool gauche;
bool droite;
int points=0;
int vies=3;



//Matrice de transformation
struct transformation
{
    mat4 rotation;
    vec3 rotation_center;
    vec3 translation;

    transformation():rotation(),rotation_center(),translation(){}
};

//Transformation des modeles
transformation transformation_model_1;
transformation transformation_model_2;
transformation transformation_model_3;
transformation transformation_model_4;
transformation transformation_model_5;
transformation transformation_model_6;
transformation transformation_model_7;
transformation transformation_model_8;
transformation transformation_model_9;
transformation transformation_model_10;


transformation transformation_tree[nbr_tree];


//Transformation de la vue (camera)
transformation transformation_view;

//Matrice de projection
mat4 projection;

//angle de deplacement
float angle_x_model_1 = 0.0f;
float angle_y_model_1 =-M_PI_2 ;

float angle_x_model_2 = 0.0f;
float angle_y_model_2 = 0.0f;

float angle_x_model_3 = 0.0f;
float angle_y_model_3 = 0.0f;

float angle_x_model_4 = 0.0f;
float angle_y_model_4 = 0.0f;

float angle_x_model_5 = 0.0f;
float angle_y_model_5 = 0.0f;

float angle_x_model_6 = 0.0f;
float angle_y_model_6 = 0.0f;

float angle_x_model_7 = 0.0f;
float angle_y_model_7 = 0.0f;

float angle_x_model_8 = 0.0f;
float angle_y_model_8 = 0.0f;


float angle_x_model_9 = 0.0f;
float angle_y_model_9 = 0.0f;

float angle_x_model_10 = 0.0f;
float angle_y_model_10 = M_PI_2;

float angle_view = 0.0f;

void load_texture(const char* filename,GLuint *texture_id);

void init_model_1();
void init_model_2();
void init_model_3();
void init_model_4();
void init_model_5();
void init_model_6();
void init_model_7();
void init_model_8();
void init_model_9();
void init_model_10();


void draw_model_1();
void draw_model_2();
void draw_model_3();
void draw_model_4();
void draw_model_5();
void draw_model_6();
void draw_model_7();
void draw_model_8();
void draw_model_9();
void draw_model_10();


void mise_a_zero();
void new_car();



static void init()
{


    // Chargement du shader
    shader_program_id = read_shader("shader.vert", "shader.frag");

    //matrice de projection
    projection = matrice_projection(60.0f*M_PI/180.0f,1.0f,0.01f,100.0f);
    glUniformMatrix4fv(get_uni_loc(shader_program_id,"projection"),1,false,pointeur(projection)); PRINT_OPENGL_ERROR();

    //centre de rotation de la 'camera' (les objets sont centres en z=-2)
    transformation_view.rotation_center = vec3(0.0f,0.0f,-2.0f);
    
    

    //activation de la gestion de la profondeur
    glEnable(GL_DEPTH_TEST); PRINT_OPENGL_ERROR();
    

    // Charge modele 1 sur la carte graphique
    init_model_1();
    // Charge modele 2 sur la carte graphique
    init_model_2();
    // Charge modele 3 sur la carte graphique
    init_model_3();
    // Charge modele 4 sur la carte graphique
    init_model_4();
    // Charge modele 5 sur la carte graphique
    init_model_5();
    // Charge modele 6 sur la carte graphique
    init_model_6();
    // Charge modele 7 sur la carte graphique
    init_model_7();
    // Charge modele 8 sur la carte graphique
    init_model_8();
    // Charge modele 9 sur la carte graphique
    init_model_9();
    // Charge modele 10 sur la carte graphique
    init_model_10();
    
    puts("Bienvenue dans notre jeu !");
    sleep(2);
    puts("Ramassez 30 pièces et vous gagnez la partie !");
    sleep(2);
    puts("Si vous êtes touché par l'ennemi, vous perdez vos points.");
    sleep(2);
    puts("Si vous êtes touché 3 fois, c'est le Game Over !");
    sleep(2);
    puts("Prêt ? Bon courage !");
    puts("Appuyez sur enter pour commencer");
    std::getchar();
     
}

//Fonction d'affichage
static void display_callback()
{
    //effacement des couleurs du fond d'ecran
    glClearColor(0.5f, 0.6f, 0.9f, 1.0f);                 PRINT_OPENGL_ERROR();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   PRINT_OPENGL_ERROR();

    // Affecte les parametres uniformes de la vue (identique pour tous les modeles de la scene)
    {
        //envoie de la rotation
        glUniformMatrix4fv(get_uni_loc(shader_program_id,"rotation_view"),1,false,pointeur(transformation_view.rotation)); PRINT_OPENGL_ERROR();

        //envoie du centre de rotation
        vec3 cv = transformation_view.rotation_center;
        glUniform4f(get_uni_loc(shader_program_id,"rotation_center_view") , cv.x,cv.y,cv.z , 0.0f); PRINT_OPENGL_ERROR();

        //envoie de la translation
        vec3 tv = transformation_view.translation;
        glUniform4f(get_uni_loc(shader_program_id,"translation_view") , tv.x,tv.y,tv.z , 0.0f); PRINT_OPENGL_ERROR();
    }

    

    // Affiche le modele numero 1 (dinosaure)
    draw_model_1();    
    // Affiche le modele numero 2 (sol)
    draw_model_2();
    // Affiche le modele numero 2 (monstre)
    draw_model_3();
    // Affiche le modele numero 4 (pavé)
    draw_model_4();
    // Affiche le modele numero 5 (Ciel devant)
    draw_model_5();
    // Affiche le modele numero 6 (Ciel gauche)
    draw_model_6();
    // Affiche le modele numero 7 (Ciel droit)
    draw_model_7();
    // Affiche le modele numero 8 (Ciel derriere)
    draw_model_8();
    // Affiche le modele numero 9 (pièce)
    draw_model_9();
    // Affiche le modele numero 10 (ennemi)
    draw_model_10();
    


    //Changement de buffer d'affichage pour eviter un effet de scintillement
    glutSwapBuffers();
}



/*****************************************************************************\
 * keyboard_callback                                                         *
\*****************************************************************************/
static void keyboard_callback(unsigned char key, int, int)
{

    //quitte le programme si on appuie sur les touches 'q', 'Q', ou 'echap'
    switch (key)
    {
    case 'q':
    case 'Q':
    case 27:
        exit(0);        

    }

}

/*****************************************************************************\
 * special_callback                                                          *
\*****************************************************************************/
static void special_callback(int key, int,int)
{

    switch (key)
    {
    case GLUT_KEY_UP:
        avant=true;
        break;
	
    case GLUT_KEY_DOWN:
        arriere=true;
        break;
	
    case GLUT_KEY_LEFT:
	gauche=true;
        break;
	
    case GLUT_KEY_RIGHT:
	droite=true;
        break;
    }

    //reactualisation de l'affichage
    glutPostRedisplay();
}

static void special_up_callback(int key, int,int)
{
    switch (key)
    {
        case GLUT_KEY_UP:           
            avant=false;            
            break;
	    
        case GLUT_KEY_DOWN:
	    arriere=false;
            break;
	    
        case GLUT_KEY_LEFT:       
            gauche=false;
            break;
	    
        case GLUT_KEY_RIGHT:           
            droite=false;
            break;
    }

}

/*****************************************************************************\
 * timer_callback                                                            *
\*****************************************************************************/

static void timer_callback(int)
{
    float dL=0.5f;
    float d_angle=0.04f;
    
    //demande de rappel de cette fonction dans 25ms
    glutTimerFunc(25, timer_callback, 0);

    if(transformation_model_9.translation.z>=1.0f ){
        
        mise_a_zero();
    }
    
    if(transformation_model_10.translation.z>=1.0f ){
        
        new_car();
    }
    
    transformation_model_1.rotation = matrice_rotation(angle_y_model_1 , 0.0f,1.0f,0.0f);
    transformation_model_9.rotation = matrice_rotation(angle_y_model_9 , 0.0f,1.0f,0.0f) ;
    transformation_model_10.rotation = matrice_rotation(angle_y_model_10 , 0.0f,1.0f,0.0f);
    transformation_view.rotation = matrice_rotation(angle_view , 0.0f,1.0f,0.0f) ;

    

    if(avant)
    {
        if( transformation_model_2.translation.x<4.0f && transformation_model_2.translation.x>-4.0)
        {
            
        transformation_model_2.translation.z -= dL*sin( angle_y_model_1);
        transformation_model_2.translation.x += dL*cos( angle_y_model_1);
        
        transformation_model_9.translation.z -= dL*sin( angle_y_model_1);
        transformation_model_9.translation.x += dL*cos( angle_y_model_1);
            
        transformation_model_10.translation.z -= dL*sin( angle_y_model_1);
        transformation_model_10.translation.x += dL*cos( angle_y_model_1);
        

        for(int i=0;i<nbr_tree;i++)
            {
                transformation_tree[i].translation.z -= dL*sin( angle_y_model_1);
                transformation_tree[i].translation.x += dL*cos( angle_y_model_1);

            }
        }
        
        if(transformation_model_2.translation.x>=4.0f && angle_view>=0.0f)
        {
            
            transformation_model_2.translation.z -= dL*sin( angle_y_model_1);
            transformation_model_2.translation.x += dL*cos( angle_y_model_1);
            
            transformation_model_9.translation.z -= dL*sin( angle_y_model_1);
            transformation_model_9.translation.x += dL*cos( angle_y_model_1);
            
            transformation_model_10.translation.z -= dL*sin( angle_y_model_1);
            transformation_model_10.translation.x += dL*cos( angle_y_model_1);
            
            
            for(int i=0;i<nbr_tree;i++)
            {
                transformation_tree[i].translation.z -= dL*sin( angle_y_model_1);
                transformation_tree[i].translation.x += dL*cos( angle_y_model_1);

            }

            
        }
        
        if(transformation_model_2.translation.x<=-4.0f && angle_view<=0.0f){
            
            transformation_model_2.translation.z -= dL*sin( angle_y_model_1);
            transformation_model_2.translation.x += dL*cos( angle_y_model_1);
            
            transformation_model_9.translation.z -= dL*sin( angle_y_model_1);
            transformation_model_9.translation.x += dL*cos( angle_y_model_1);
            
            transformation_model_10.translation.z -= dL*sin( angle_y_model_1);
            transformation_model_10.translation.x += dL*cos( angle_y_model_1);
            
            
            for(int i=0;i<nbr_tree;i++)
            {
                transformation_tree[i].translation.z -= dL*sin( angle_y_model_1);
                transformation_tree[i].translation.x += dL*cos( angle_y_model_1);
                transformation_tree[i].rotation_center.z -= dL*cos( angle_y_model_1);
                transformation_tree[i].rotation_center.x += dL*sin( angle_y_model_1);
            }
            
            
        }



    }
    

    
    if(gauche)// && transformation_model_2.translation.x<=4.0f)
    {
        if(angle_view>=-M_PI_2 && angle_view<M_PI_2)
        {
            angle_view -= d_angle;
            angle_y_model_1 += d_angle;
        }
        if(angle_view>=M_PI_2){
            angle_view -= d_angle;
            angle_y_model_1 += d_angle;
        }

    
    }
    
    if(droite)// && transformation_model_2.translation.x>=-4.0f)
    {
        
        if(angle_view>-M_PI_2 && angle_view<=M_PI_2)
        {
            angle_view += d_angle;
            angle_y_model_1 -= d_angle;
        }
        if(angle_view<-M_PI_2){
            angle_view += d_angle;
            angle_y_model_1 -= d_angle;
        }


    }
    
    // récupération de l'objet
    if(transformation_model_9.translation.x<=0.5f && transformation_model_9.translation.x>=-0.5f && transformation_model_9.translation.z<=0.3f && transformation_model_9.translation.z>=-0.3f )
    {
        points++;
        if (points==1) printf("Vous avez %d point. \n",points);
        else printf("Vous avez %d points. \n",points);
        mise_a_zero();
        
    }
    
    // touché par l'ennemi
    if(transformation_model_10.translation.x<=0.65f && transformation_model_10.translation.x>=-0.65f && transformation_model_10.translation.z<=1.4f && transformation_model_10.translation.z>=-1.4f )
    {
        vies--;
        points=0;
        if (vies>1) printf(" AIE !! Attention, Il vous reste %d vies avant le Game Over ! Vous avez 0 point. \n",vies);
        if (vies==1)  printf(" AIE !! Attention, Il vous reste %d vie avant le Game Over ! Vous avez 0 point. \n",vies);
        new_car();
        
        
    }
    
    // pièce tourne sur place
    angle_y_model_9+=d_angle;
    
    //ennemi avance tout seul
    transformation_model_10.translation.z+=dL-0.2f;
    
    if (points==30) {
        puts("VICTOIRE !!!");
        exit(1);
    }
    if(vies==0){
        printf("GAME OVER... Réessayez! \n");
        exit(1);
    }
    //reactualisation de l'affichage
    glutPostRedisplay();
}

void mise_a_zero()
{
    
    // mise à zéro de la route
    transformation_model_2.translation.z=0.0f;
    
    //mise à zéro des arbres
    transformation_tree[0].translation.z=-50.0f;
    transformation_tree[1].translation.z=-50.0f;
    for(int i=2;i<nbr_tree;i++)
    {
        
        transformation_tree[i].translation.z=transformation_tree[i-2].translation.z+10.0f;
        
    }
    
    //mise à zéro de la pièce
    transformation_model_9.translation.z=-30.0f;
    float n=rand()%7-3;
    transformation_model_9.translation.x=transformation_model_2.translation.x+ n;
    
}

void new_car()
{
    transformation_model_10.translation.z=-30.0f;
    float n=rand()%7-3;
    transformation_model_10.translation.x=transformation_model_2.translation.x+ n;
    
}

/*void ecrire (const char *text, int length, int x, int y){

    glMatrixMode(GL_PROJECTION);
    double *matric = new double[16];
    glGetDOublev(GL_PROJECTION_MATRIX, matrix);
    glLoadIdentity();
    glOrtho(0, 800, 0, 600, -5, 5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(x, y);
    for(int i=0; i<length, i++){
        gluBitmapCharacter(GLUT_BITMAP_9_By15, (int)text[i]);
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(matrix);
    glMatricMode(GL_MODELVIEW);
    
}

void DrawScreen(*/

int main(int argc, char** argv)
{
    //**********************************************//
    //Lancement des fonctions principales de GLUT
    //**********************************************//

    //initialisation
    glutInit(&argc, argv);

    //Mode d'affichage (couleur, gestion de profondeur, ...)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    //Taille de la fenetre a l'ouverture
    glutInitWindowSize(600, 600);

    //Titre de la fenetre
    glutCreateWindow("OpenGL");

    //Fonction de la boucle d'affichage
    glutDisplayFunc(display_callback);

    //Fonction de gestion du clavier
    glutKeyboardFunc(keyboard_callback);

    //Fonction des touches speciales du clavier (fleches directionnelles)
    glutSpecialFunc(special_callback);
    glutSpecialUpFunc(special_up_callback);

    //Fonction d'appel d'affichage en chaine
    glutTimerFunc(25, timer_callback, 0);

    //Initialisation des fonctions OpenGL
    glewInit();

    //Notre fonction d'initialisation des donnees et chargement des shaders
    init();
    
    //Lancement de la boucle (infinie) d'affichage de la fenetre
    glutMainLoop();

    //Plus rien n'est execute apres cela

    return 0;
}

void draw_model_1()
{

    //envoie des parametres uniformes
    {
        glUniformMatrix4fv(get_uni_loc(shader_program_id,"rotation_model"),1,false,pointeur(transformation_model_1.rotation));    PRINT_OPENGL_ERROR();

        vec3 c = transformation_model_1.rotation_center;
        glUniform4f(get_uni_loc(shader_program_id,"rotation_center_model") , c.x,c.y,c.z , 0.0f);                                 PRINT_OPENGL_ERROR();

        vec3 t = transformation_model_1.translation;
        glUniform4f(get_uni_loc(shader_program_id,"translation_model") , t.x,t.y,t.z , 0.0f);                                     PRINT_OPENGL_ERROR();
    }

    //placement des VBO
    {
        //selection du VBO courant
        glBindBuffer(GL_ARRAY_BUFFER,vbo_object_1);                                                    PRINT_OPENGL_ERROR();

        // mise en place des differents pointeurs
        glEnableClientState(GL_VERTEX_ARRAY);                                                          PRINT_OPENGL_ERROR();
        glVertexPointer(3, GL_FLOAT, sizeof(vertex_opengl), 0);                                        PRINT_OPENGL_ERROR();

        glEnableClientState(GL_NORMAL_ARRAY); PRINT_OPENGL_ERROR();                                    PRINT_OPENGL_ERROR();
        glNormalPointer(GL_FLOAT, sizeof(vertex_opengl), buffer_offset(sizeof(vec3)));                 PRINT_OPENGL_ERROR();

        glEnableClientState(GL_COLOR_ARRAY); PRINT_OPENGL_ERROR();                                     PRINT_OPENGL_ERROR();
        glColorPointer(3,GL_FLOAT, sizeof(vertex_opengl), buffer_offset(2*sizeof(vec3)));              PRINT_OPENGL_ERROR();

        glEnableClientState(GL_TEXTURE_COORD_ARRAY); PRINT_OPENGL_ERROR();                             PRINT_OPENGL_ERROR();
        glTexCoordPointer(2,GL_FLOAT, sizeof(vertex_opengl), buffer_offset(3*sizeof(vec3)));           PRINT_OPENGL_ERROR();

    }

    //affichage
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vboi_object_1);                           PRINT_OPENGL_ERROR();
        glBindTexture(GL_TEXTURE_2D, texture_id_object_1);                             PRINT_OPENGL_ERROR();
        glDrawElements(GL_TRIANGLES, 3*nbr_triangle_object_1, GL_UNSIGNED_INT, 0);     PRINT_OPENGL_ERROR();
    }

}

void draw_model_2()
{

    //envoie des parametres uniformes
    {
        glUniformMatrix4fv(get_uni_loc(shader_program_id,"rotation_model"),1,false,pointeur(transformation_model_2.rotation));    PRINT_OPENGL_ERROR();

        vec3 c = transformation_model_2.rotation_center;
        glUniform4f(get_uni_loc(shader_program_id,"rotation_center_model") , c.x,c.y,c.z , 0.0f);                                 PRINT_OPENGL_ERROR();

        vec3 t = transformation_model_2.translation;
        glUniform4f(get_uni_loc(shader_program_id,"translation_model") , t.x,t.y,t.z , 0.0f);                                     PRINT_OPENGL_ERROR();
    }

    //placement des VBO
    {
        //selection du VBO courant
        glBindBuffer(GL_ARRAY_BUFFER,vbo_object_2);                                                    PRINT_OPENGL_ERROR();

        // mise en place des differents pointeurs
        glEnableClientState(GL_VERTEX_ARRAY);                                                          PRINT_OPENGL_ERROR();
        glVertexPointer(3, GL_FLOAT, sizeof(vertex_opengl), 0);                                        PRINT_OPENGL_ERROR();

        glEnableClientState(GL_NORMAL_ARRAY); PRINT_OPENGL_ERROR();                                    PRINT_OPENGL_ERROR();
        glNormalPointer(GL_FLOAT, sizeof(vertex_opengl), buffer_offset(sizeof(vec3)));                 PRINT_OPENGL_ERROR();

        glEnableClientState(GL_COLOR_ARRAY); PRINT_OPENGL_ERROR();                                     PRINT_OPENGL_ERROR();
        glColorPointer(3,GL_FLOAT, sizeof(vertex_opengl), buffer_offset(2*sizeof(vec3)));              PRINT_OPENGL_ERROR();

        glEnableClientState(GL_TEXTURE_COORD_ARRAY); PRINT_OPENGL_ERROR();                             PRINT_OPENGL_ERROR();
        glTexCoordPointer(2,GL_FLOAT, sizeof(vertex_opengl), buffer_offset(3*sizeof(vec3)));           PRINT_OPENGL_ERROR();

    }

    //affichage
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vboi_object_2);                           PRINT_OPENGL_ERROR();
        glBindTexture(GL_TEXTURE_2D, texture_id_object_2);                             PRINT_OPENGL_ERROR();
        glDrawElements(GL_TRIANGLES, 3*nbr_triangle_object_2, GL_UNSIGNED_INT, 0);     PRINT_OPENGL_ERROR();
    }
}

void draw_model_3()
{
    for(int i=0;i<nbr_tree;i++)
    {
        glUniformMatrix4fv(get_uni_loc(shader_program_id,"rotation_model"),1,false,pointeur(transformation_tree[i].rotation));    PRINT_OPENGL_ERROR();

        vec3 c = transformation_tree[i].rotation_center;
        glUniform4f(get_uni_loc(shader_program_id,"rotation_center_model") , c.x,c.y,c.z , 0.0f);                                 PRINT_OPENGL_ERROR();

        vec3 t = transformation_tree[i].translation;
        glUniform4f(get_uni_loc(shader_program_id,"translation_model") , t.x,t.y,t.z , 0.0f);                                     PRINT_OPENGL_ERROR();
    

    //placement des VBO
    {
        //selection du VBO courant
        glBindBuffer(GL_ARRAY_BUFFER,vbo_object_3);                                                    PRINT_OPENGL_ERROR();

        // mise en place des differents pointeurs
        glEnableClientState(GL_VERTEX_ARRAY);                                                          PRINT_OPENGL_ERROR();
        glVertexPointer(3, GL_FLOAT, sizeof(vertex_opengl), 0);                                        PRINT_OPENGL_ERROR();

        glEnableClientState(GL_NORMAL_ARRAY); PRINT_OPENGL_ERROR();                                    PRINT_OPENGL_ERROR();
        glNormalPointer(GL_FLOAT, sizeof(vertex_opengl), buffer_offset(sizeof(vec3)));                 PRINT_OPENGL_ERROR();

        glEnableClientState(GL_COLOR_ARRAY); PRINT_OPENGL_ERROR();                                     PRINT_OPENGL_ERROR();
        glColorPointer(3,GL_FLOAT, sizeof(vertex_opengl), buffer_offset(2*sizeof(vec3)));              PRINT_OPENGL_ERROR();

        glEnableClientState(GL_TEXTURE_COORD_ARRAY); PRINT_OPENGL_ERROR();                             PRINT_OPENGL_ERROR();
        glTexCoordPointer(2,GL_FLOAT, sizeof(vertex_opengl), buffer_offset(3*sizeof(vec3)));           PRINT_OPENGL_ERROR();

    }

    //affichage
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vboi_object_3);                           PRINT_OPENGL_ERROR();
        glBindTexture(GL_TEXTURE_2D, texture_id_object_3);                             PRINT_OPENGL_ERROR();
    
         glDrawElements(GL_TRIANGLES, 3*nbr_triangle_object_3, GL_UNSIGNED_INT, 0);     PRINT_OPENGL_ERROR();
    }}
}

void draw_model_4()
{

    //envoie des parametres uniformes
    {
        glUniformMatrix4fv(get_uni_loc(shader_program_id,"rotation_model"),1,false,pointeur(transformation_model_4.rotation));    PRINT_OPENGL_ERROR();

        vec3 c = transformation_model_4.rotation_center;
        glUniform4f(get_uni_loc(shader_program_id,"rotation_center_model") , c.x,c.y,c.z , 0.0f);                                 PRINT_OPENGL_ERROR();

        vec3 t = transformation_model_4.translation;
        glUniform4f(get_uni_loc(shader_program_id,"translation_model") , t.x,t.y,t.z , 0.0f);                                     PRINT_OPENGL_ERROR();
    }

    //placement des VBO
    {
        //selection du VBO courant
        glBindBuffer(GL_ARRAY_BUFFER,vbo_object_4);                                                    PRINT_OPENGL_ERROR();

        // mise en place des differents pointeurs
        glEnableClientState(GL_VERTEX_ARRAY);                                                          PRINT_OPENGL_ERROR();
        glVertexPointer(3, GL_FLOAT, sizeof(vertex_opengl), 0);                                        PRINT_OPENGL_ERROR();

        glEnableClientState(GL_NORMAL_ARRAY); PRINT_OPENGL_ERROR();                                    PRINT_OPENGL_ERROR();
        glNormalPointer(GL_FLOAT, sizeof(vertex_opengl), buffer_offset(sizeof(vec3)));                 PRINT_OPENGL_ERROR();

        glEnableClientState(GL_COLOR_ARRAY); PRINT_OPENGL_ERROR();                                     PRINT_OPENGL_ERROR();
        glColorPointer(3,GL_FLOAT, sizeof(vertex_opengl), buffer_offset(2*sizeof(vec3)));              PRINT_OPENGL_ERROR();

        glEnableClientState(GL_TEXTURE_COORD_ARRAY); PRINT_OPENGL_ERROR();                             PRINT_OPENGL_ERROR();
        glTexCoordPointer(2,GL_FLOAT, sizeof(vertex_opengl), buffer_offset(3*sizeof(vec3)));           PRINT_OPENGL_ERROR();

    }

    //affichage
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vboi_object_4);                           PRINT_OPENGL_ERROR();
        glBindTexture(GL_TEXTURE_2D, texture_id_object_4);                             PRINT_OPENGL_ERROR();
        glDrawElements(GL_TRIANGLES, 3*nbr_triangle_object_4, GL_UNSIGNED_INT, 0);     PRINT_OPENGL_ERROR();
    }
}

void draw_model_5()
{

    //envoie des parametres uniformes
    {
        glUniformMatrix4fv(get_uni_loc(shader_program_id,"rotation_model"),1,false,pointeur(transformation_model_5.rotation));    PRINT_OPENGL_ERROR();

        vec3 c = transformation_model_5.rotation_center;
        glUniform4f(get_uni_loc(shader_program_id,"rotation_center_model") , c.x,c.y,c.z , 0.0f);                                 PRINT_OPENGL_ERROR();

        vec3 t = transformation_model_5.translation;
        glUniform4f(get_uni_loc(shader_program_id,"translation_model") , t.x,t.y,t.z , 0.0f);                                     PRINT_OPENGL_ERROR();
    }

    //placement des VBO
    {
        //selection du VBO courant
        glBindBuffer(GL_ARRAY_BUFFER,vbo_object_5);                                                    PRINT_OPENGL_ERROR();

        // mise en place des differents pointeurs
        glEnableClientState(GL_VERTEX_ARRAY);                                                          PRINT_OPENGL_ERROR();
        glVertexPointer(3, GL_FLOAT, sizeof(vertex_opengl), 0);                                        PRINT_OPENGL_ERROR();

        glEnableClientState(GL_NORMAL_ARRAY); PRINT_OPENGL_ERROR();                                    PRINT_OPENGL_ERROR();
        glNormalPointer(GL_FLOAT, sizeof(vertex_opengl), buffer_offset(sizeof(vec3)));                 PRINT_OPENGL_ERROR();

        glEnableClientState(GL_COLOR_ARRAY); PRINT_OPENGL_ERROR();                                     PRINT_OPENGL_ERROR();
        glColorPointer(3,GL_FLOAT, sizeof(vertex_opengl), buffer_offset(2*sizeof(vec3)));              PRINT_OPENGL_ERROR();

        glEnableClientState(GL_TEXTURE_COORD_ARRAY); PRINT_OPENGL_ERROR();                             PRINT_OPENGL_ERROR();
        glTexCoordPointer(2,GL_FLOAT, sizeof(vertex_opengl), buffer_offset(3*sizeof(vec3)));           PRINT_OPENGL_ERROR();

    }

    //affichage
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vboi_object_5);                           PRINT_OPENGL_ERROR();
        glBindTexture(GL_TEXTURE_2D, texture_id_object_5);                             PRINT_OPENGL_ERROR();
        glDrawElements(GL_TRIANGLES, 3*nbr_triangle_object_5, GL_UNSIGNED_INT, 0);     PRINT_OPENGL_ERROR();
    }
}

void draw_model_6()
{

    //envoie des parametres uniformes
    {
        glUniformMatrix4fv(get_uni_loc(shader_program_id,"rotation_model"),1,false,pointeur(transformation_model_6.rotation));    PRINT_OPENGL_ERROR();

        vec3 c = transformation_model_6.rotation_center;
        glUniform4f(get_uni_loc(shader_program_id,"rotation_center_model") , c.x,c.y,c.z , 0.0f);                                 PRINT_OPENGL_ERROR();

        vec3 t = transformation_model_6.translation;
        glUniform4f(get_uni_loc(shader_program_id,"translation_model") , t.x,t.y,t.z , 0.0f);                                     PRINT_OPENGL_ERROR();
    }

    //placement des VBO
    {
        //selection du VBO courant
        glBindBuffer(GL_ARRAY_BUFFER,vbo_object_6);                                                    PRINT_OPENGL_ERROR();

        // mise en place des differents pointeurs
        glEnableClientState(GL_VERTEX_ARRAY);                                                          PRINT_OPENGL_ERROR();
        glVertexPointer(3, GL_FLOAT, sizeof(vertex_opengl), 0);                                        PRINT_OPENGL_ERROR();

        glEnableClientState(GL_NORMAL_ARRAY); PRINT_OPENGL_ERROR();                                    PRINT_OPENGL_ERROR();
        glNormalPointer(GL_FLOAT, sizeof(vertex_opengl), buffer_offset(sizeof(vec3)));                 PRINT_OPENGL_ERROR();

        glEnableClientState(GL_COLOR_ARRAY); PRINT_OPENGL_ERROR();                                     PRINT_OPENGL_ERROR();
        glColorPointer(3,GL_FLOAT, sizeof(vertex_opengl), buffer_offset(2*sizeof(vec3)));              PRINT_OPENGL_ERROR();

        glEnableClientState(GL_TEXTURE_COORD_ARRAY); PRINT_OPENGL_ERROR();                             PRINT_OPENGL_ERROR();
        glTexCoordPointer(2,GL_FLOAT, sizeof(vertex_opengl), buffer_offset(3*sizeof(vec3)));           PRINT_OPENGL_ERROR();

    }

    //affichage
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vboi_object_6);                           PRINT_OPENGL_ERROR();
        glBindTexture(GL_TEXTURE_2D, texture_id_object_6);                             PRINT_OPENGL_ERROR();
        glDrawElements(GL_TRIANGLES, 3*nbr_triangle_object_6, GL_UNSIGNED_INT, 0);     PRINT_OPENGL_ERROR();
    }
}

void draw_model_7()
{

    //envoie des parametres uniformes
    {
        glUniformMatrix4fv(get_uni_loc(shader_program_id,"rotation_model"),1,false,pointeur(transformation_model_7.rotation));    PRINT_OPENGL_ERROR();

        vec3 c = transformation_model_7.rotation_center;
        glUniform4f(get_uni_loc(shader_program_id,"rotation_center_model") , c.x,c.y,c.z , 0.0f);                                 PRINT_OPENGL_ERROR();

        vec3 t = transformation_model_7.translation;
        glUniform4f(get_uni_loc(shader_program_id,"translation_model") , t.x,t.y,t.z , 0.0f);                                     PRINT_OPENGL_ERROR();
    }

    //placement des VBO
    {
        //selection du VBO courant
        glBindBuffer(GL_ARRAY_BUFFER,vbo_object_7);                                                    PRINT_OPENGL_ERROR();

        // mise en place des differents pointeurs
        glEnableClientState(GL_VERTEX_ARRAY);                                                          PRINT_OPENGL_ERROR();
        glVertexPointer(3, GL_FLOAT, sizeof(vertex_opengl), 0);                                        PRINT_OPENGL_ERROR();

        glEnableClientState(GL_NORMAL_ARRAY); PRINT_OPENGL_ERROR();                                    PRINT_OPENGL_ERROR();
        glNormalPointer(GL_FLOAT, sizeof(vertex_opengl), buffer_offset(sizeof(vec3)));                 PRINT_OPENGL_ERROR();

        glEnableClientState(GL_COLOR_ARRAY); PRINT_OPENGL_ERROR();                                     PRINT_OPENGL_ERROR();
        glColorPointer(3,GL_FLOAT, sizeof(vertex_opengl), buffer_offset(2*sizeof(vec3)));              PRINT_OPENGL_ERROR();

        glEnableClientState(GL_TEXTURE_COORD_ARRAY); PRINT_OPENGL_ERROR();                             PRINT_OPENGL_ERROR();
        glTexCoordPointer(2,GL_FLOAT, sizeof(vertex_opengl), buffer_offset(3*sizeof(vec3)));           PRINT_OPENGL_ERROR();

    }

    //affichage
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vboi_object_7);                           PRINT_OPENGL_ERROR();
        glBindTexture(GL_TEXTURE_2D, texture_id_object_7);                             PRINT_OPENGL_ERROR();
        glDrawElements(GL_TRIANGLES, 3*nbr_triangle_object_7, GL_UNSIGNED_INT, 0);     PRINT_OPENGL_ERROR();
    }
}

void draw_model_8()
{

    //envoie des parametres uniformes
    {
        glUniformMatrix4fv(get_uni_loc(shader_program_id,"rotation_model"),1,false,pointeur(transformation_model_8.rotation));    PRINT_OPENGL_ERROR();

        vec3 c = transformation_model_8.rotation_center;
        glUniform4f(get_uni_loc(shader_program_id,"rotation_center_model") , c.x,c.y,c.z , 0.0f);                                 PRINT_OPENGL_ERROR();

        vec3 t = transformation_model_8.translation;
        glUniform4f(get_uni_loc(shader_program_id,"translation_model") , t.x,t.y,t.z , 0.0f);                                     PRINT_OPENGL_ERROR();
    }

    //placement des VBO
    {
        //selection du VBO courant
        glBindBuffer(GL_ARRAY_BUFFER,vbo_object_8);                                                    PRINT_OPENGL_ERROR();

        // mise en place des differents pointeurs
        glEnableClientState(GL_VERTEX_ARRAY);                                                          PRINT_OPENGL_ERROR();
        glVertexPointer(3, GL_FLOAT, sizeof(vertex_opengl), 0);                                        PRINT_OPENGL_ERROR();

        glEnableClientState(GL_NORMAL_ARRAY); PRINT_OPENGL_ERROR();                                    PRINT_OPENGL_ERROR();
        glNormalPointer(GL_FLOAT, sizeof(vertex_opengl), buffer_offset(sizeof(vec3)));                 PRINT_OPENGL_ERROR();

        glEnableClientState(GL_COLOR_ARRAY); PRINT_OPENGL_ERROR();                                     PRINT_OPENGL_ERROR();
        glColorPointer(3,GL_FLOAT, sizeof(vertex_opengl), buffer_offset(2*sizeof(vec3)));              PRINT_OPENGL_ERROR();

        glEnableClientState(GL_TEXTURE_COORD_ARRAY); PRINT_OPENGL_ERROR();                             PRINT_OPENGL_ERROR();
        glTexCoordPointer(2,GL_FLOAT, sizeof(vertex_opengl), buffer_offset(3*sizeof(vec3)));           PRINT_OPENGL_ERROR();

    }

    //affichage
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vboi_object_8);                           PRINT_OPENGL_ERROR();
        glBindTexture(GL_TEXTURE_2D, texture_id_object_8);                             PRINT_OPENGL_ERROR();
        glDrawElements(GL_TRIANGLES, 3*nbr_triangle_object_8, GL_UNSIGNED_INT, 0);     PRINT_OPENGL_ERROR();
    }
}

void draw_model_9()
{
    
    //envoie des parametres uniformes
    {
        glUniformMatrix4fv(get_uni_loc(shader_program_id,"rotation_model"),1,false,pointeur(transformation_model_9.rotation));    PRINT_OPENGL_ERROR();
        
        vec3 c = transformation_model_9.rotation_center;
        glUniform4f(get_uni_loc(shader_program_id,"rotation_center_model") , c.x,c.y,c.z , 0.0f);                                 PRINT_OPENGL_ERROR();
        
        vec3 t = transformation_model_9.translation;
        glUniform4f(get_uni_loc(shader_program_id,"translation_model") , t.x,t.y,t.z , 0.0f);                                     PRINT_OPENGL_ERROR();
    }
    
    //placement des VBO
    {
        //selection du VBO courant
        glBindBuffer(GL_ARRAY_BUFFER,vbo_object_9);                                                    PRINT_OPENGL_ERROR();
        
        // mise en place des differents pointeurs
        glEnableClientState(GL_VERTEX_ARRAY);                                                          PRINT_OPENGL_ERROR();
        glVertexPointer(3, GL_FLOAT, sizeof(vertex_opengl), 0);                                        PRINT_OPENGL_ERROR();
        
        glEnableClientState(GL_NORMAL_ARRAY); PRINT_OPENGL_ERROR();                                    PRINT_OPENGL_ERROR();
        glNormalPointer(GL_FLOAT, sizeof(vertex_opengl), buffer_offset(sizeof(vec3)));                 PRINT_OPENGL_ERROR();
        
        glEnableClientState(GL_COLOR_ARRAY); PRINT_OPENGL_ERROR();                                     PRINT_OPENGL_ERROR();
        glColorPointer(3,GL_FLOAT, sizeof(vertex_opengl), buffer_offset(2*sizeof(vec3)));              PRINT_OPENGL_ERROR();
        
        glEnableClientState(GL_TEXTURE_COORD_ARRAY); PRINT_OPENGL_ERROR();                             PRINT_OPENGL_ERROR();
        glTexCoordPointer(2,GL_FLOAT, sizeof(vertex_opengl), buffer_offset(3*sizeof(vec3)));           PRINT_OPENGL_ERROR();
        
    }
    
    //affichage
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vboi_object_9);                           PRINT_OPENGL_ERROR();
        glBindTexture(GL_TEXTURE_2D, texture_id_object_9);                             PRINT_OPENGL_ERROR();
        glDrawElements(GL_TRIANGLES, 3*nbr_triangle_object_9, GL_UNSIGNED_INT, 0);     PRINT_OPENGL_ERROR();
    }
    
}

void draw_model_10()
{
    
    //envoie des parametres uniformes
    {
        glUniformMatrix4fv(get_uni_loc(shader_program_id,"rotation_model"),1,false,pointeur(transformation_model_10.rotation));    PRINT_OPENGL_ERROR();
        
        vec3 c = transformation_model_10.rotation_center;
        glUniform4f(get_uni_loc(shader_program_id,"rotation_center_model") , c.x,c.y,c.z , 0.0f);                                 PRINT_OPENGL_ERROR();
        
        vec3 t = transformation_model_10.translation;
        glUniform4f(get_uni_loc(shader_program_id,"translation_model") , t.x,t.y,t.z , 0.0f);                                     PRINT_OPENGL_ERROR();
    }
    
    //placement des VBO
    {
        //selection du VBO courant
        glBindBuffer(GL_ARRAY_BUFFER,vbo_object_10);                                                    PRINT_OPENGL_ERROR();
        
        // mise en place des differents pointeurs
        glEnableClientState(GL_VERTEX_ARRAY);                                                          PRINT_OPENGL_ERROR();
        glVertexPointer(3, GL_FLOAT, sizeof(vertex_opengl), 0);                                        PRINT_OPENGL_ERROR();
        
        glEnableClientState(GL_NORMAL_ARRAY); PRINT_OPENGL_ERROR();                                    PRINT_OPENGL_ERROR();
        glNormalPointer(GL_FLOAT, sizeof(vertex_opengl), buffer_offset(sizeof(vec3)));                 PRINT_OPENGL_ERROR();
        
        glEnableClientState(GL_COLOR_ARRAY); PRINT_OPENGL_ERROR();                                     PRINT_OPENGL_ERROR();
        glColorPointer(3,GL_FLOAT, sizeof(vertex_opengl), buffer_offset(2*sizeof(vec3)));              PRINT_OPENGL_ERROR();
        
        glEnableClientState(GL_TEXTURE_COORD_ARRAY); PRINT_OPENGL_ERROR();                             PRINT_OPENGL_ERROR();
        glTexCoordPointer(2,GL_FLOAT, sizeof(vertex_opengl), buffer_offset(3*sizeof(vec3)));           PRINT_OPENGL_ERROR();
        
    }
    
    //affichage
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vboi_object_10);                           PRINT_OPENGL_ERROR();
        glBindTexture(GL_TEXTURE_2D, texture_id_object_10);                             PRINT_OPENGL_ERROR();
        glDrawElements(GL_TRIANGLES, 3*nbr_triangle_object_10, GL_UNSIGNED_INT, 0);     PRINT_OPENGL_ERROR();
    }
    
}

void init_model_1()
{
    // Chargement d'un maillage a partir d'un fichier
    mesh m = load_obj_file("../data/Avent.obj");

    // Affecte une transformation sur les sommets du maillage
    float s = 0.2f;
    mat4 transform = mat4(   s, 0.0f, 0.0f, 0.0f,
                          0.0f,    s, 0.0f,-0.9f,
                          0.0f, 0.0f,   s ,-2.0f,
                          0.0f, 0.0f, 0.0f, 1.0f);
    apply_deformation(&m,transform);

    // Centre la rotation du modele 1 autour de son centre de gravite approximatif
    transformation_model_1.rotation_center = vec3(0.0f,-0.5f,-2.0f);

    // Calcul automatique des normales du maillage
    update_normals(&m);
    // Les sommets sont affectes a une couleur blanche
    fill_color(&m,vec3(1.0f,1.0f,1.0f));

    //attribution d'un buffer de donnees (1 indique la création d'un buffer)
    glGenBuffers(1,&vbo_object_1); PRINT_OPENGL_ERROR();
    //affectation du buffer courant
    glBindBuffer(GL_ARRAY_BUFFER,vbo_object_1); PRINT_OPENGL_ERROR();
    //copie des donnees des sommets sur la carte graphique
    glBufferData(GL_ARRAY_BUFFER,m.vertex.size()*sizeof(vertex_opengl),&m.vertex[0],GL_STATIC_DRAW); PRINT_OPENGL_ERROR();


    //attribution d'un autre buffer de donnees
    glGenBuffers(1,&vboi_object_1); PRINT_OPENGL_ERROR();
    //affectation du buffer courant (buffer d'indice)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vboi_object_1); PRINT_OPENGL_ERROR();
    //copie des indices sur la carte graphique
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,m.connectivity.size()*sizeof(triangle_index),&m.connectivity[0],GL_STATIC_DRAW); PRINT_OPENGL_ERROR();

    // Nombre de triangles de l'objet 1
    nbr_triangle_object_1 = m.connectivity.size();

    // Chargement de la texture
    load_texture("../data/white.tga",&texture_id_object_1);


}

void init_model_2()
{
    //Creation manuelle du model 2

    //coordonnees geometriques des sommets
    vec3 p0=vec3(-5.0f,-0.9f,-50.0f);
    vec3 p1=vec3(5.0f,-0.9f,-50.0f);
    vec3 p2=vec3(5.0f,-0.9f,50.0f);
    vec3 p3=vec3(-5.0f,-0.9f,50.0f);

    //normales pour chaque sommet
    vec3 n0=vec3(0.0f,1.0f,0.0f);
    vec3 n1=n0;
    vec3 n2=n0;
    vec3 n3=n0;

    //couleur pour chaque sommet
    vec3 c0=vec3(1.0f,1.0f,1.0f);
    vec3 c1=c0;
    vec3 c2=c0;
    vec3 c3=c0;

    //texture du sommet
    vec2 t0=vec2(0.0f,0.0f);
    vec2 t1=vec2(1.0f,0.0f);
    vec2 t2=vec2(1.0f,1.0f);
    vec2 t3=vec2(0.0f,1.0f);

    vertex_opengl v0=vertex_opengl(p0,n0,c0,t0);
    vertex_opengl v1=vertex_opengl(p1,n1,c1,t1);
    vertex_opengl v2=vertex_opengl(p2,n2,c2,t2);
    vertex_opengl v3=vertex_opengl(p3,n3,c3,t3);


    //tableau entrelacant coordonnees-normales
    vertex_opengl geometrie[]={v0,v1,v2,v3};


    //indice des triangles
    triangle_index tri0=triangle_index(0,1,2);
    triangle_index tri1=triangle_index(0,2,3);
    triangle_index index[]={tri0,tri1};
    nbr_triangle_object_2 = 2;

    //attribution d'un buffer de donnees (1 indique la création d'un buffer)
    glGenBuffers(1,&vbo_object_2);                                             PRINT_OPENGL_ERROR();
    //affectation du buffer courant
    glBindBuffer(GL_ARRAY_BUFFER,vbo_object_2);                                PRINT_OPENGL_ERROR();
    //copie des donnees des sommets sur la carte graphique
    glBufferData(GL_ARRAY_BUFFER,sizeof(geometrie),geometrie,GL_STATIC_DRAW);  PRINT_OPENGL_ERROR();


    //attribution d'un autre buffer de donnees
    glGenBuffers(1,&vboi_object_2);                                            PRINT_OPENGL_ERROR();
    //affectation du buffer courant (buffer d'indice)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vboi_object_2);                       PRINT_OPENGL_ERROR();
    //copie des indices sur la carte graphique
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(index),index,GL_STATIC_DRAW);  PRINT_OPENGL_ERROR();

    // Chargement de la texture
    load_texture("../data/street2LanesSpec.tga",&texture_id_object_2);

}

void init_model_3()
{
    // Chargement d'un maillage a partir d'un fichier
    mesh m = load_obj_file("../data/Tree.obj");

    // Affecte une transformation sur les sommets du maillage
    float s = 0.01f;
    mat4 transform = mat4(   s, 0.0f, 0.0f, 1.0f,
                          0.0f,    s, 0.0f,0.0f,
                          0.0f, 0.0f,   s ,-2.0f,
                          0.0f, 0.0f, 0.0f, 1.0f);
    
    transformation_tree[0].translation.x=5.0f;
    transformation_tree[0].translation.y=-0.9f;
    transformation_tree[0].translation.z=-50.0f;
    transformation_tree[1].translation.x=-7.0f;
    transformation_tree[1].translation.y=-0.9f;
    transformation_tree[1].translation.z=-50.0f;
   
    for(int i=0;i<nbr_tree;i++){
        transformation_tree[i].rotation_center=transformation_model_2.rotation_center;
    }
    
    for(int i=2;i<nbr_tree;i++){
        
        transformation_tree[i].translation.z=transformation_tree[i-2].translation.z+10.0f;
        transformation_tree[i].translation.y= transformation_tree[i-2].translation.y;
        transformation_tree[i].translation.x=transformation_tree[i-2].translation.x;

        

    }

    
    apply_deformation(&m,transform);

    // Calcul automatique des normales du maillage
    update_normals(&m);
    // Les sommets sont affectes a une couleur blanche
    fill_color(&m,vec3(1.0f,1.0f,1.0f));

    //attribution d'un buffer de donnees (1 indique la création d'un buffer)
    glGenBuffers(1,&vbo_object_3);                                 PRINT_OPENGL_ERROR();
    //affectation du buffer courant
    glBindBuffer(GL_ARRAY_BUFFER,vbo_object_3); PRINT_OPENGL_ERROR();
    //copie des donnees des sommets sur la carte graphique
    glBufferData(GL_ARRAY_BUFFER,m.vertex.size()*sizeof(vertex_opengl),&m.vertex[0],GL_STATIC_DRAW); PRINT_OPENGL_ERROR();


    //attribution d'un autre buffer de donnees
    glGenBuffers(1,&vboi_object_3); PRINT_OPENGL_ERROR();
    //affectation du buffer courant (buffer d'indice)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vboi_object_3); PRINT_OPENGL_ERROR();
    //copie des indices sur la carte graphique
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,m.connectivity.size()*sizeof(triangle_index),&m.connectivity[0],GL_STATIC_DRAW); PRINT_OPENGL_ERROR();

    // Nombre de triangles de l'objet 3
    nbr_triangle_object_3 = m.connectivity.size();

    // Chargement de la texture
    load_texture("../data/Tree.tga",&texture_id_object_3);

}

void init_model_4()
{
    //Creation manuelle du model 4

    //coordonnees geometriques des sommets
    vec3 p0=vec3(-50.0f,-1.0f,-50.0f);
    vec3 p1=vec3(50.0f,-1.0f,-50.0f);
    vec3 p2=vec3(50.0f,-1.0f,50.0f);
    vec3 p3=vec3(-50.0f,-1.0f,50.0f);

    //normales pour chaque sommet
    vec3 n0=vec3(0.0f,1.0f,0.0f);
    vec3 n1=n0;
    vec3 n2=n0;
    vec3 n3=n0;

    //couleur pour chaque sommet
    vec3 c0=vec3(1.0f,1.0f,1.0f);
    vec3 c1=c0;
    vec3 c2=c0;
    vec3 c3=c0;

    //texture du sommet
    vec2 t0=vec2(0.0f,0.0f);
    vec2 t1=vec2(1.0f,0.0f);
    vec2 t2=vec2(1.0f,1.0f);
    vec2 t3=vec2(0.0f,1.0f);

    vertex_opengl v0=vertex_opengl(p0,n0,c0,t0);
    vertex_opengl v1=vertex_opengl(p1,n1,c1,t1);
    vertex_opengl v2=vertex_opengl(p2,n2,c2,t2);
    vertex_opengl v3=vertex_opengl(p3,n3,c3,t3);


    //tableau entrelacant coordonnees-normales
    vertex_opengl geometrie[]={v0,v1,v2,v3};


    //indice des triangles
    triangle_index tri0=triangle_index(0,1,2);
    triangle_index tri1=triangle_index(0,2,3);
    triangle_index index[]={tri0,tri1};
    nbr_triangle_object_4 = 2;

    //attribution d'un buffer de donnees (1 indique la création d'un buffer)
    glGenBuffers(1,&vbo_object_4);                                             PRINT_OPENGL_ERROR();
    //affectation du buffer courant
    glBindBuffer(GL_ARRAY_BUFFER,vbo_object_4);                                PRINT_OPENGL_ERROR();
    //copie des donnees des sommets sur la carte graphique
    glBufferData(GL_ARRAY_BUFFER,sizeof(geometrie),geometrie,GL_STATIC_DRAW);  PRINT_OPENGL_ERROR();


    //attribution d'un autre buffer de donnees
    glGenBuffers(1,&vboi_object_4);                                            PRINT_OPENGL_ERROR();
    //affectation du buffer courant (buffer d'indice)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vboi_object_4);                       PRINT_OPENGL_ERROR();
    //copie des indices sur la carte graphique
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(index),index,GL_STATIC_DRAW);  PRINT_OPENGL_ERROR();

    // Chargement de la texture
    load_texture("../data/Stone_floor.tga",&texture_id_object_4);

}

void init_model_5()
{
    //Creation manuelle du model 5

    //coordonnees geometriques des sommets
    vec3 p0=vec3(-50.0f,-1.0f,-50.0f);
    vec3 p1=vec3(50.0f,-1.0f,-50.0f);
    vec3 p2=vec3(50.0f,50.0f,-50.0f);
    vec3 p3=vec3(-50.0f,50.0f,-50.0f);

    //normales pour chaque sommet
    vec3 n0=vec3(0.0f,1.0f,0.0f);
    vec3 n1=n0;
    vec3 n2=n0;
    vec3 n3=n0;

    //couleur pour chaque sommet
    vec3 c0=vec3(1.0f,1.0f,1.0f);
    vec3 c1=c0;
    vec3 c2=c0;
    vec3 c3=c0;

    //texture du sommet
    vec2 t0=vec2(0.0f,0.0f);
    vec2 t1=vec2(1.0f,0.0f);
    vec2 t2=vec2(1.0f,1.0f);
    vec2 t3=vec2(0.0f,1.0f);

    vertex_opengl v0=vertex_opengl(p0,n0,c0,t0);
    vertex_opengl v1=vertex_opengl(p1,n1,c1,t1);
    vertex_opengl v2=vertex_opengl(p2,n2,c2,t2);
    vertex_opengl v3=vertex_opengl(p3,n3,c3,t3);


    //tableau entrelacant coordonnees-normales
    vertex_opengl geometrie[]={v0,v1,v2,v3};


    //indice des triangles
    triangle_index tri0=triangle_index(0,1,2);
    triangle_index tri1=triangle_index(0,2,3);
    triangle_index index[]={tri0,tri1};
    nbr_triangle_object_5 = 2;

    //attribution d'un buffer de donnees (1 indique la création d'un buffer)
    glGenBuffers(1,&vbo_object_5);                                             PRINT_OPENGL_ERROR();
    //affectation du buffer courant
    glBindBuffer(GL_ARRAY_BUFFER,vbo_object_5);                                PRINT_OPENGL_ERROR();
    //copie des donnees des sommets sur la carte graphique
    glBufferData(GL_ARRAY_BUFFER,sizeof(geometrie),geometrie,GL_STATIC_DRAW);  PRINT_OPENGL_ERROR();


    //attribution d'un autre buffer de donnees
    glGenBuffers(1,&vboi_object_5);                                            PRINT_OPENGL_ERROR();
    //affectation du buffer courant (buffer d'indice)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vboi_object_5);                       PRINT_OPENGL_ERROR();
    //copie des indices sur la carte graphique
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(index),index,GL_STATIC_DRAW);  PRINT_OPENGL_ERROR();

    // Chargement de la texture
    load_texture("../data/Ciel.tga",&texture_id_object_5);

}

void init_model_6()
{
    //Creation manuelle du model 6

    //coordonnees geometriques des sommets
    vec3 p0=vec3(-50.0f,-1.0f,-50.0f);
    vec3 p1=vec3(-50.0f,-1.0f,50.0f);
    vec3 p2=vec3(-50.0f,50.0f,50.0f);
    vec3 p3=vec3(-50.0f,50.0f,-50.0f);

    //normales pour chaque sommet
    vec3 n0=vec3(0.0f,1.0f,0.0f);
    vec3 n1=n0;
    vec3 n2=n0;
    vec3 n3=n0;

    //couleur pour chaque sommet
    vec3 c0=vec3(1.0f,1.0f,1.0f);
    vec3 c1=c0;
    vec3 c2=c0;
    vec3 c3=c0;

    //texture du sommet
    vec2 t0=vec2(0.0f,0.0f);
    vec2 t1=vec2(1.0f,0.0f);
    vec2 t2=vec2(1.0f,1.0f);
    vec2 t3=vec2(0.0f,1.0f);

    vertex_opengl v0=vertex_opengl(p0,n0,c0,t0);
    vertex_opengl v1=vertex_opengl(p1,n1,c1,t1);
    vertex_opengl v2=vertex_opengl(p2,n2,c2,t2);
    vertex_opengl v3=vertex_opengl(p3,n3,c3,t3);


    //tableau entrelacant coordonnees-normales
    vertex_opengl geometrie[]={v0,v1,v2,v3};


    //indice des triangles
    triangle_index tri0=triangle_index(0,1,2);
    triangle_index tri1=triangle_index(0,2,3);
    triangle_index index[]={tri0,tri1};
    nbr_triangle_object_6 = 2;

    //attribution d'un buffer de donnees (1 indique la création d'un buffer)
    glGenBuffers(1,&vbo_object_6);                                             PRINT_OPENGL_ERROR();
    //affectation du buffer courant
    glBindBuffer(GL_ARRAY_BUFFER,vbo_object_6);                                PRINT_OPENGL_ERROR();
    //copie des donnees des sommets sur la carte graphique
    glBufferData(GL_ARRAY_BUFFER,sizeof(geometrie),geometrie,GL_STATIC_DRAW);  PRINT_OPENGL_ERROR();


    //attribution d'un autre buffer de donnees
    glGenBuffers(1,&vboi_object_6);                                            PRINT_OPENGL_ERROR();
    //affectation du buffer courant (buffer d'indice)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vboi_object_6);                       PRINT_OPENGL_ERROR();
    //copie des indices sur la carte graphique
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(index),index,GL_STATIC_DRAW);  PRINT_OPENGL_ERROR();

    // Chargement de la texture
    load_texture("../data/Ciel.tga",&texture_id_object_6);

}

void init_model_7()
{
    //Creation manuelle du model 7

    //coordonnees geometriques des sommets
    vec3 p0=vec3(50.0f,-1.0f,50.0f);
    vec3 p1=vec3(50.0f,-1.0f,-50.0f);
    vec3 p2=vec3(50.0f,50.0f,-50.0f);
    vec3 p3=vec3(50.0f,50.0f,50.0f);

    //normales pour chaque sommet
    vec3 n0=vec3(0.0f,1.0f,0.0f);
    vec3 n1=n0;
    vec3 n2=n0;
    vec3 n3=n0;

    //couleur pour chaque sommet
    vec3 c0=vec3(1.0f,1.0f,1.0f);
    vec3 c1=c0;
    vec3 c2=c0;
    vec3 c3=c0;

    //texture du sommet
    vec2 t0=vec2(0.0f,0.0f);
    vec2 t1=vec2(1.0f,0.0f);
    vec2 t2=vec2(1.0f,1.0f);
    vec2 t3=vec2(0.0f,1.0f);

    vertex_opengl v0=vertex_opengl(p0,n0,c0,t0);
    vertex_opengl v1=vertex_opengl(p1,n1,c1,t1);
    vertex_opengl v2=vertex_opengl(p2,n2,c2,t2);
    vertex_opengl v3=vertex_opengl(p3,n3,c3,t3);


    //tableau entrelacant coordonnees-normales
    vertex_opengl geometrie[]={v0,v1,v2,v3};


    //indice des triangles
    triangle_index tri0=triangle_index(0,1,2);
    triangle_index tri1=triangle_index(0,2,3);
    triangle_index index[]={tri0,tri1};
    nbr_triangle_object_7 = 2;

    //attribution d'un buffer de donnees (1 indique la création d'un buffer)
    glGenBuffers(1,&vbo_object_7);                                             PRINT_OPENGL_ERROR();
    //affectation du buffer courant
    glBindBuffer(GL_ARRAY_BUFFER,vbo_object_7);                                PRINT_OPENGL_ERROR();
    //copie des donnees des sommets sur la carte graphique
    glBufferData(GL_ARRAY_BUFFER,sizeof(geometrie),geometrie,GL_STATIC_DRAW);  PRINT_OPENGL_ERROR();


    //attribution d'un autre buffer de donnees
    glGenBuffers(1,&vboi_object_7);                                            PRINT_OPENGL_ERROR();
    //affectation du buffer courant (buffer d'indice)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vboi_object_7);                       PRINT_OPENGL_ERROR();
    //copie des indices sur la carte graphique
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(index),index,GL_STATIC_DRAW);  PRINT_OPENGL_ERROR();

    // Chargement de la texture
    load_texture("../data/Ciel.tga",&texture_id_object_7);

}

void init_model_8()
{
    //Creation manuelle du model 8

    //coordonnees geometriques des sommets
    vec3 p0=vec3(-50.0f,-1.0f,50.0f);
    vec3 p1=vec3(50.0f,-1.0f,50.0f);
    vec3 p2=vec3(50.0f,50.0f,50.0f);
    vec3 p3=vec3(-50.0f,50.0f,50.0f);

    //normales pour chaque sommet
    vec3 n0=vec3(0.0f,1.0f,0.0f);
    vec3 n1=n0;
    vec3 n2=n0;
    vec3 n3=n0;

    //couleur pour chaque sommet
    vec3 c0=vec3(1.0f,1.0f,1.0f);
    vec3 c1=c0;
    vec3 c2=c0;
    vec3 c3=c0;

    //texture du sommet
    vec2 t0=vec2(0.0f,0.0f);
    vec2 t1=vec2(1.0f,0.0f);
    vec2 t2=vec2(1.0f,1.0f);
    vec2 t3=vec2(0.0f,1.0f);

    vertex_opengl v0=vertex_opengl(p0,n0,c0,t0);
    vertex_opengl v1=vertex_opengl(p1,n1,c1,t1);
    vertex_opengl v2=vertex_opengl(p2,n2,c2,t2);
    vertex_opengl v3=vertex_opengl(p3,n3,c3,t3);


    //tableau entrelacant coordonnees-normales
    vertex_opengl geometrie[]={v0,v1,v2,v3};


    //indice des triangles
    triangle_index tri0=triangle_index(0,1,2);
    triangle_index tri1=triangle_index(0,2,3);
    triangle_index index[]={tri0,tri1};
    nbr_triangle_object_8 = 2;

    //attribution d'un buffer de donnees (1 indique la création d'un buffer)
    glGenBuffers(1,&vbo_object_8);                                             PRINT_OPENGL_ERROR();
    //affectation du buffer courant
    glBindBuffer(GL_ARRAY_BUFFER,vbo_object_8);                                PRINT_OPENGL_ERROR();
    //copie des donnees des sommets sur la carte graphique
    glBufferData(GL_ARRAY_BUFFER,sizeof(geometrie),geometrie,GL_STATIC_DRAW);  PRINT_OPENGL_ERROR();


    //attribution d'un autre buffer de donnees
    glGenBuffers(1,&vboi_object_8);                                            PRINT_OPENGL_ERROR();
    //affectation du buffer courant (buffer d'indice)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vboi_object_8);                       PRINT_OPENGL_ERROR();
    //copie des indices sur la carte graphique
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(index),index,GL_STATIC_DRAW);  PRINT_OPENGL_ERROR();

    // Chargement de la texture
    load_texture("../data/Ciel.tga",&texture_id_object_8);
   
}

void init_model_9()
{
    // Chargement d'un maillage a partir d'un fichier
    mesh m = load_obj_file("../data/coin.obj");
    
    // Affecte une transformation sur les sommets du maillage
    float s = 0.05f;
    mat4 transform = mat4(   s, 0.0f, 0.0f, 0.0f,
                          0.0f,    s, 0.0f,-0.9f,
                          0.0f, 0.0f,   s ,-2.0f,
                          0.0f, 0.0f, 0.0f, 1.0f);
    apply_deformation(&m,transform);
    
    transformation_model_9.translation.x=0.0f;
    transformation_model_9.translation.z=-30.0f;
    transformation_model_9.rotation_center.z = transformation_model_9.translation.z;
    transformation_model_9.rotation_center.x = transformation_model_9.translation.x;
    
    
    // Centre la rotation du modele 9 autour de son centre de gravite approximatif
    transformation_model_9.rotation_center = vec3(0.0f,-0.5f,-2.0f);
    
    // Calcul automatique des normales du maillage
    update_normals(&m);
    
    // Les sommets sont affectes a une couleur blanche
    fill_color(&m,vec3(1.0f,1.0f,1.0f));
    
    //attribution d'un buffer de donnees (1 indique la création d'un buffer)
    glGenBuffers(1,&vbo_object_9); PRINT_OPENGL_ERROR();
    //affectation du buffer courant
    glBindBuffer(GL_ARRAY_BUFFER,vbo_object_9); PRINT_OPENGL_ERROR();
    //copie des donnees des sommets sur la carte graphique
    glBufferData(GL_ARRAY_BUFFER,m.vertex.size()*sizeof(vertex_opengl),&m.vertex[0],GL_STATIC_DRAW); PRINT_OPENGL_ERROR();
    
    
    //attribution d'un autre buffer de donnees
    glGenBuffers(1,&vboi_object_9); PRINT_OPENGL_ERROR();
    //affectation du buffer courant (buffer d'indice)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vboi_object_9); PRINT_OPENGL_ERROR();
    //copie des indices sur la carte graphique
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,m.connectivity.size()*sizeof(triangle_index),&m.connectivity[0],GL_STATIC_DRAW); PRINT_OPENGL_ERROR();
    
    // Nombre de triangles de l'objet 9
    nbr_triangle_object_9 = m.connectivity.size();
    
    // Chargement de la texture
    load_texture("../data/coin.tga",&texture_id_object_9);
    
    
}

void init_model_10()
{
    // Chargement d'un maillage a partir d'un fichier
    mesh m = load_obj_file("../data/Avent.obj");
    
    // Affecte une transformation sur les sommets du maillage
    float s = 0.3f;
    mat4 transform = mat4(   s, 0.0f, 0.0f, 0.0f,
                          0.0f,    s, 0.0f,-0.9f,
                          0.0f, 0.0f,   s ,-2.0f,
                          0.0f, 0.0f, 0.0f, 1.0f);
    apply_deformation(&m,transform);
    
    transformation_model_10.translation.x=3.0f;
    transformation_model_10.translation.z=-20.0f;
    
    
    
    // Centre la rotation du modele 1 autour de son centre de gravite approximatif
    transformation_model_10.rotation_center = vec3(0.0f,-0.5f,-2.0f);
    
    // Calcul automatique des normales du maillage
    update_normals(&m);
    // Les sommets sont affectes a une couleur blanche
    fill_color(&m,vec3(1.0f,1.0f,1.0f));
    
    //attribution d'un buffer de donnees (1 indique la création d'un buffer)
    glGenBuffers(1,&vbo_object_10); PRINT_OPENGL_ERROR();
    //affectation du buffer courant
    glBindBuffer(GL_ARRAY_BUFFER,vbo_object_10); PRINT_OPENGL_ERROR();
    //copie des donnees des sommets sur la carte graphique
    glBufferData(GL_ARRAY_BUFFER,m.vertex.size()*sizeof(vertex_opengl),&m.vertex[0],GL_STATIC_DRAW); PRINT_OPENGL_ERROR();
    
    
    //attribution d'un autre buffer de donnees
    glGenBuffers(1,&vboi_object_10); PRINT_OPENGL_ERROR();
    //affectation du buffer courant (buffer d'indice)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vboi_object_10); PRINT_OPENGL_ERROR();
    //copie des indices sur la carte graphique
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,m.connectivity.size()*sizeof(triangle_index),&m.connectivity[0],GL_STATIC_DRAW); PRINT_OPENGL_ERROR();
    
    // Nombre de triangles de l'objet 1
    nbr_triangle_object_10 = m.connectivity.size();
    
    // Chargement de la texture
    load_texture("../data/rouge.tga",&texture_id_object_10);
    
    
}



void load_texture(const char* filename,GLuint *texture_id)
{
    // Chargement d'une texture (seul les textures tga sont supportes)
    Image  *image = image_load_tga(filename);
    if (image) //verification que l'image est bien chargee
    {

        //Creation d'un identifiant pour la texture
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); PRINT_OPENGL_ERROR();
        glGenTextures(1, texture_id); PRINT_OPENGL_ERROR();

        //Selection de la texture courante a partir de son identifiant
        glBindTexture(GL_TEXTURE_2D, *texture_id); PRINT_OPENGL_ERROR();

        //Parametres de la texture
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); PRINT_OPENGL_ERROR();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); PRINT_OPENGL_ERROR();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); PRINT_OPENGL_ERROR();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); PRINT_OPENGL_ERROR();

        //Envoie de l'image en memoire video
        if(image->type==IMAGE_TYPE_RGB){ //image RGB
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->data); PRINT_OPENGL_ERROR();}
        else if(image->type==IMAGE_TYPE_RGBA){ //image RGBA
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->width, image->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->data); PRINT_OPENGL_ERROR();}
        else{
            std::cout<<"Image type not handled"<<std::endl;}

        delete image;
    }
    else
    {
        std::cerr<<"Erreur chargement de l'image, etes-vous dans le bon repertoire?"<<std::endl;
        abort();
    }

    glUniform1i (get_uni_loc(shader_program_id, "texture"), 0); PRINT_OPENGL_ERROR();
}


