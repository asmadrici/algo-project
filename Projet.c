#include <raylib.h>
#include <stddef.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// enfile 
void enqueue(Queue* q, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    if (q->rear == NULL) {
       // ida la file vide
        q->front = q->rear = newNode;
    } else {
        // ajoute un element ala fin de la file
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

// defiler
int dequeue(Queue* q) {
    if (q->front == NULL) {
        // ida la file vide
        return -1;
    }

    // supp l'element 
    Node* temp = q->front;
    int value = temp->data;

    q->front = temp->next;

    if (q->front == NULL) {
        // la fille elle est vide
        q->rear = NULL;
    }

    free(temp);

    return value;
}
// dessin tae l'element
void drawQueue(Queue* q) {
    Node* current = q->front;
    int xPos = 100;
    const int yPos = 200;
    const int horizontalSpacing = 80;
    const int circleRadius = 20;  // Radius of the circles

    while (current != NULL) {
        DrawCircle(xPos + circleRadius, yPos + circleRadius, circleRadius, BLUE);
        DrawText(TextFormat("%d", current->data), xPos, yPos, 20, WHITE);

        if (current->next != NULL) {
            DrawLine(xPos + circleRadius * 2, yPos + circleRadius, xPos + circleRadius * 2 + horizontalSpacing, yPos + circleRadius, BLACK);
        }

        xPos += horizontalSpacing;
        current = current->next;
    }
}

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;

     char errorMessage[256] = "";  // Variable to store the error message

    InitWindow(screenWidth, screenHeight, "Les files");

    SetTargetFPS(60);

    Queue q = { .front = NULL, .rear = NULL };
    int nodeCount = 0;// to not make more than 11 file

    while (!WindowShouldClose()) {
      

        //  si le bouton  est clique
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            // les coordonnees du clic
            int mouseX = GetMouseX();
            int mouseY = GetMouseY();

            // si on a clicque  enfiler
           if (CheckCollisionPointRec((Vector2){mouseX, mouseY}, (Rectangle){600, 50, 100, 40})) {
            if (nodeCount <= 7)
            {
                strcpy(errorMessage, "");
            
                enqueue(&q, GetRandomValue(10, 99));
                nodeCount++;
            }else{
             strcpy(errorMessage, "La file est pleine !");
            }
            
                
             
            }

            // si on a clicque defiler
            if (CheckCollisionPointRec((Vector2){mouseX, mouseY}, (Rectangle){600, 100, 100, 40})) {
                if (q.front != NULL) {
                    strcpy(errorMessage, "");
                    dequeue(&q);
                    nodeCount--;
                } else {
                    // Display an error message when trying to dequeue from an empty queue
                    strcpy(errorMessage, "Error: La file est vide!");
                }
                
            }

            // i on a clicque Quitter
            if (CheckCollisionPointRec((Vector2){mouseX, mouseY}, (Rectangle){600, 150, 100, 40})) {
                CloseWindow();  // hna fermer la fenetre
            }
        }

        BeginDrawing();

        ClearBackground(GRAY);

        // dessiner la file
        drawQueue(&q);

        // dessiner enfiler
        DrawRectangle(600, 50, 100, 40, PINK);
        DrawText("Enfiler", 615, 60, 20, WHITE);

        // dessine le bouton defiler
        DrawRectangle(600, 100, 100, 40, PINK);
        DrawText("Defiler", 615, 110, 20, WHITE);

        // dessine le bouton Quitter
        DrawRectangle(600, 150, 100, 40, PINK);
        DrawText("Quitter", 615, 160, 20, WHITE);

        DrawText(errorMessage, 10, 10, 20, RED);

        EndDrawing();
    }

    // liberation
    Node* current = q.front;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }

    CloseWindow();

    return 0;
}
