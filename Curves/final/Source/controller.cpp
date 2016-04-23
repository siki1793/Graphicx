#ifndef HEADER_EH
#define HEADER_EH
#include "exh.h"
#endif

void controller::mouseEventHandler(int button,int state,int x,int y){
    view cv;
	POINT M,P=control_p[0];
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){//if left-button is clicked then a new control point will be draw
        if(pic)
        {
            cout<<"x : "<<x<<" y : "<<y<<endl;
            x=x-SCREEN_WIDTH/2;
            y=SCREEN_HEIGHT/2-y;
            control_p[p_count].x=(float)x;
            control_p[p_count].y=(float)y;
            cout<<"x "<<control_p[p_count].x<<" and y "<<control_p[p_count].y<<" is stored "<<endl;
            cout<<"insert points"<<endl;
            p_count++;
            for(i=0;i<=p_count-1;i++)
            {
                cout<<"x "<<control_p[i].x<<" y "<<control_p[i].y<<endl;
            }
            if(x>=-SCREEN_WIDTH/2 && x<=lower_x)
                lower_x=x;
            if(x<=SCREEN_WIDTH/2 && x>=upper_x)
                upper_x=x;

            cv.drawPoint(x,y);
		}

    }
	else
    if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
    {
        if(del)
        {
            int pos=0,found=0;
            cout<<"x : "<<x<<" y : "<<y<<endl;
            x=x-SCREEN_WIDTH/2;
            y=SCREEN_HEIGHT/2-y;
            cout<<"x "<<x<<" and y "<<y<<" is stored "<<endl;
                for (i = 0; i < p_count; i++)
                {
                    if ((abs(abs(control_p[i].x) - abs(x)) < 5) && (abs(abs(control_p[i].y) - abs(y)) < 5))
                    {

                        found = 1;
                        cout<<"found x "<<control_p[i].x<<"y "<<control_p[i].y<<endl;
                        pos = i;
                        break;
                    }
                }
                printf("Enter the element to be deleted\n");
                if (found == 1)
                {
                    printf("Enter the element to be deleted\n");
                    for (i = pos; i <  p_count - 1; i++)
                    {
                        control_p[i].x = control_p[i+1].x;
                        control_p[i].y = control_p[i+1].y;
                    }
                    //deletePoint(control_p[p_count-1].x,control_p[p_count-1].y);

                    for(i=0;i<p_count-1;i++)
                    {
                        cout<<"x "<<control_p[i].x<<" y "<<control_p[i].y<<endl;
                    }
                    p_count--;
                    glutPostRedisplay();
            }
        }
        if(click)
        {
            cout<<"inside translate"<<endl;
            //twopoints.clear();
            cout<<"x : "<<x<<" y : "<<y<<endl;
            x=x-SCREEN_WIDTH/2;
            y=SCREEN_HEIGHT/2-y;

            if(flag==0)
            {
            cout<<"x "<<x<<" and y "<<y<<" is stored "<<endl;
                two_px1=(float)x;
                two_py1=(float)y;
            }
            if(flag==1)
            {
            cout<<"x "<<x<<" and y "<<y<<" is stored "<<endl;
                two_px2=(float)x;
                two_py2=(float)y;
            }
            flag++;
            glutPostRedisplay();
        }
    }
}


void controller::keyboardEventHandler(unsigned char key,int x, int y){
    view cv;
    if(key == 'w'){
    cout<<"up"<<endl;
        distanceY += 2.;
        glutPostRedisplay();
    }
    else if(key == 's'){
    cout<<"down"<<endl;
        distanceY -= 2.;
        glutPostRedisplay();
    }
    else if(key == 'd'){
    cout<<"right"<<endl;
        distanceX += 2.;
        glutPostRedisplay();
    }
    else if(key == 'a'){
    cout<<"left"<<endl;
        distanceX -= 2.;
        glutPostRedisplay();
    }
    else if(key == '+')
    {
        cout<<"zoom out"<<endl;
        scale = scale * 1.2;
        glutPostRedisplay();
    }
    else if(key == '-')
    {
        cout<<"zoom in"<<endl;
        scale = scale / (float)1.2;
        glutPostRedisplay();
    }
    else if(key == 'q')
    {
        flag = 0;
        del=false;
        pic=true;
        settranslate=false;
    }
    else if(key == 'e')
    {
        flag = 0;
        del=true;
        pic=false;
        settranslate=false;
    }
    else if(key == 't')
    {
        cout<<"inside two points switch"<<endl;
        settranslate=true;
        cout<<settranslate<<endl;
        cout<<"flag "<<flag<<endl;

        del=false;
        pic=false;
        glutPostRedisplay();
    }
    else if(key == 'i')
    {
        click=true;
        del=false;
        pic=false;
    }

switch (key) {
      case 'c':
            cv.renderFunction();
            break;
      case '1':
         cout<<"curve switched"<<endl;
         loadBezier = true;
         loadLagrange=true;
         glutPostRedisplay();
         break;
      case '2':
         loadBezier = false;
         loadLagrange=false;
         glutPostRedisplay();
         break;

      case 'r':
         Angle += 20.;
         setangle=true;
         glutPostRedisplay();
         break;
      case 'l':
         Angle -= 20.;
         setangle=true;
         glutPostRedisplay();
         break;
      case 'D':
      for(i=0;i<p_count-1;i++)
					cv.drawLine(control_p[i],control_p[i+1]);
					break;
      case 27:  /*  Escape Key  */
         exit(0);
         break;
      default:
         break;
    }
}
