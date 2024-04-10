#include <iostream>
#include<graphics.h>
#include <unistd.h>
using namespace std;
typedef struct Point {
    int x, y;
} Point;

int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

void convexHull(Point points[], int n) {
    if (n < 3) return;
    setcolor(14);
    int hullIndices[n];
    for (int i = 0; i < n; i++) hullIndices[i] = -1;

    int leftmost = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].x < points[leftmost].x)
            leftmost = i;
    }
    sleep(1);
    int p = leftmost, q;
    int arr[n][n];
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            arr[i][j] = 0;
        }
    }
    do {
        q = (p + 1) % n;
        line(points[p].x*100+50, 450 - points[p].y*100, 50+ points[q].x*100, 450 - 100*points[q].y);
        sleep(1);
        for (int i = 0; i < n; i++) {
        line(points[i].x*100+50, 450 - points[i].y*100, 50+ points[q].x*100, 450 - 100*points[q].y);
        sleep(1);
            if (orientation(points[p], points[i], points[q]) == 2){
                    if(i!=p && i!=q){
                            if(arr[i][q]!=1){
                                setcolor(0);
                                line(points[i].x*100+50, 450 - points[i].y*100, 50+ points[q].x*100, 450 - 100*points[q].y);
                                putpixel(points[i].x*100+50,450 - points[i].y*100,WHITE);
                                putpixel(points[q].x*100+50,450 - points[q].y*100,WHITE);
                                sleep(1);
                            }
                            if(arr[p][q]!=1){
                                setcolor(0);
                                line(points[p].x*100+50, 450 - points[p].y*100, 50+ points[q].x*100, 450 - 100*points[q].y);
                                putpixel(points[p].x*100+50,450 - points[p].y*100,WHITE);
                                putpixel(points[q].x*100+50,450 - points[q].y*100,WHITE);
                                sleep(1);
                            }
                        q = i;
                        setcolor(14);
                        line(points[p].x*100+50, 450 - points[p].y*100, 50+ points[q].x*100, 450 - 100*points[q].y);
                        sleep(1);
                    }
            }
            else{
                    if(i!=p && i!=q){
                            if(arr[i][q]!=1){
                                setcolor(0);
                                line(points[i].x*100+50, 450 - points[i].y*100, 50+ points[q].x*100, 450 - 100*points[q].y);
                                putpixel(points[i].x*100+50,450 - points[i].y*100,WHITE);
                                putpixel(points[q].x*100+50,450 - points[q].y*100,WHITE);
                                setcolor(14);
                            }
                    }

            }
            for(int i = 0; i<n; i++){
                putpixel(points[i].x*100 + 50, 450 - points[i].y*100, WHITE);
            }
        }

        arr[p][q] = 1;
        arr[q][p] = 1;
        line(points[p].x*100+50, 450 - points[p].y*100, 50+ points[q].x*100, 450 - 100*points[q].y);
        hullIndices[p] = q;
        p = q;
    } while (p != leftmost);

    // Printing the convex hull points
    //for (int i = 0; i < n; i++) {
      //  if (hullIndices[i] != -1)
        //    printf("(%d, %d)\n", points[i].x, points[i].y);
    //}
}

int main()
{
    int gd=DETECT, gm; // Detect is constant value of graphics driver and is assigned to gd , gm will hold the value of graphics mode
    initgraph(&gd,&gm, "");
    Point points[] = {{0, 3}, {1, 1}, {2, 2}, {4, 4}, {0, 0}, {1, 2}, {3, 3},{3,1}, {5,2}};
    int n = sizeof(points) / sizeof(points[0]);
    line(50,100,50,450);
    line(51, 450,600, 450);
    setcolor(4);
    for(int i = 0; i<n; i++){
        putpixel(points[i].x*100 + 50, 450 - points[i].y*100, WHITE);
    }
    convexHull(points, n);
    getch();
    closegraph();
    return 0;
}
