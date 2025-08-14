#include <stdio.h>
#include <math.h>
#include <graphics.h>

struct Point {
    float x, y;
};

void drawTriangle(struct Point t[3], int color) {
    setcolor(color);
    line(t[0].x, t[0].y, t[1].x, t[1].y);
    line(t[1].x, t[1].y, t[2].x, t[2].y);
    line(t[2].x, t[2].y, t[0].x, t[0].y);
}

void translate(struct Point t[3], float tx, float ty) {
    for (int i = 0; i < 3; i++) {
        t[i].x += tx;
        t[i].y += ty;
    }
}

void scale(struct Point t[3], float sx, float sy) {
    for (int i = 0; i < 3; i++) {
        t[i].x *= sx;
        t[i].y *= sy;
    }
}

void rotateTriangle(struct Point t[3], float angle) {
    float rad = angle * M_PI / 180.0;
    for (int i = 0; i < 3; i++) {
        float x_new = t[i].x * cos(rad) - t[i].y * sin(rad);
        float y_new = t[i].x * sin(rad) + t[i].y * cos(rad);
        t[i].x = x_new;
        t[i].y = y_new;
    }
}

void reflect(struct Point t[3], int axis) {
    for (int i = 0; i < 3; i++) {
        if (axis == 1) t[i].y = -t[i].y;       // X-axis
        else if (axis == 2) t[i].x = -t[i].x;  // Y-axis
        else if (axis == 3) {                  // Origin
            t[i].x = -t[i].x;
            t[i].y = -t[i].y;
        }
    }
}

void shear(struct Point t[3], float shx, float shy) {
    for (int i = 0; i < 3; i++) {
        float x_new = t[i].x + shx * t[i].y;
        float y_new = t[i].y + shy * t[i].x;
        t[i].x = x_new;
        t[i].y = y_new;
    }
}

int main() {
    struct Point tri[3];
    int gd = DETECT, gm;
    int choice;

    printf("Enter coordinates of triangle vertices (x y):\n");
    for (int i = 0; i < 3; i++) {
        scanf("%f %f", &tri[i].x, &tri[i].y);
    }

    initgraph(&gd, &gm, ""); // Initialize graphics mode

    while (1) {
        cleardevice();
        drawTriangle(tri, WHITE);

        printf("\n--- 2D Triangle Transformations ---\n");
        printf("1. Translation\n2. Scaling\n3. Rotation\n4. Reflection\n5. Shearing\n6. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        if (choice == 6) break;

        switch (choice) {
            case 1: {
                float tx, ty;
                printf("Enter tx and ty: ");
                scanf("%f %f", &tx, &ty);
                translate(tri, tx, ty);
                break;
            }
            case 2: {
                float sx, sy;
                printf("Enter sx and sy: ");
                scanf("%f %f", &sx, &sy);
                scale(tri, sx, sy);
                break;
            }
            case 3: {
                float angle;
                printf("Enter rotation angle (degrees): ");
                scanf("%f", &angle);
                rotateTriangle(tri, angle);
                break;
            }
            case 4: {
                int axis;
                printf("Reflect over: 1.X-axis  2.Y-axis  3.Origin : ");
                scanf("%d", &axis);
                reflect(tri, axis);
                break;
            }
            case 5: {
                float shx, shy;
                printf("Enter shx and shy: ");
                scanf("%f %f", &shx, &shy);
                shear(tri, shx, shy);
                break;
            }
            default:
                printf("Invalid choice!\n");
        }
    }

    closegraph();
    return 0;
}
