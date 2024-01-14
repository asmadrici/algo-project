#include <raylib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include <malloc.h>

// Declaration d une file
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
        // la file elle est vide
        q->rear = NULL;
    }
    free(temp);
    return value;

}
// dessin tae l'element
void drawQueue(Queue* q) {
    Node* current = q->front;
    int xPos = 67;
    const int yPos = 230;
    const int horizontalSpacing = 100;
    const int rectangleWidth = 60;  // Width of the rectangles
    const int rectangleHeight = 40; // Height of the rectangles

    while (current != NULL) {
        // Draw the rectangle
        DrawRectangle(xPos, yPos, rectangleWidth, rectangleHeight, (Color){0xD5, 0xBD, 0xAF, 0xFF});

        // Calculate the position to center the text inside the rectangle
        int textWidth = MeasureText(TextFormat("%d", current->data), 20);
        int textX = xPos + (rectangleWidth - textWidth) / 2;
        int textY = yPos + (rectangleHeight - 20) / 2; // Adjust based on your font size

        DrawText(TextFormat("%d", current->data), textX, textY, 20, WHITE);

        if (current->next != NULL) {
            DrawLine(xPos + rectangleWidth, yPos + rectangleHeight / 2, xPos + rectangleWidth + horizontalSpacing, yPos + rectangleHeight / 2, BLACK);
        }

        xPos += horizontalSpacing;
        current = current->next;
    }
}
int main(void) {

    const int screenWidth = 800;
    const int screenHeight = 450;
    char errorMessage[256] = "";  // Variable to store the error message

    InitWindow(screenWidth, screenHeight, "LES FILES"); // Initial window

    SetTargetFPS(23);

    Queue q = { .front = NULL, .rear = NULL };// initialision de la file

    int nodeCount = 0; // compteur d'elements de la file
    
    char inputValue[5] = {0};  // To store user input as string
    int inputIndex = 0;  // To keep track of the current index in inputValue
    bool inputMode = false;

    float circleRadius = 25.0f;  // Radius of the circles
  
    Vector2 enfilerButtonPosition = {600, 50};
    Rectangle enfilerButton = {enfilerButtonPosition.x, enfilerButtonPosition.y, 100, 40};
    Vector2 inputButtonCenter = {enfilerButtonPosition.x + enfilerButton.width + 10 + circleRadius, enfilerButtonPosition.y + enfilerButton.height / 2};
    bool showInputButton = false;


    while (!WindowShouldClose()) {
        //  si le bouton  est clique
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            // les coordonnees du clic
            int mouseX = GetMouseX();
            int mouseY = GetMouseY();

            // si on a clicque  enfiler
             if (CheckCollisionPointRec((Vector2){mouseX, mouseY}, enfilerButton)) {
                 if (nodeCount < 7) // pour que le nombre d'elements ne depasse pas 7 elemnets
            {
                strcpy(errorMessage, ""); // pour supprimer le message erreur dans la cas d enfiler une file vide

                // Activate input mode
                inputMode = true;
                // Reset input values
                inputValue[0] = '\0';
                inputIndex = 0;

                //increase counter
                nodeCount++;

                // Show the input button
                    showInputButton = true;
            }else{
             strcpy(errorMessage, "Error: La file est pleine ! \n"
            "\n(La file n'a pas de maximum mais pour des \n"
              "\n raison de graphique on a mis une limite)");
            }
            }else {
                // Si on clique sur un autre bouton, désactiver le mode d'entrée
                inputMode = false;
                // Hide the input button
                showInputButton = false;
            }

            // si on a clicque defiler
            if (CheckCollisionPointRec((Vector2){mouseX, mouseY}, (Rectangle){600, 100, 100, 40})) {
                 if (q.front != NULL) {
                    strcpy(errorMessage, "");// pour supprimer le message erreur dans la cas d enfiler une file vide
                    dequeue(&q);

                    //decrease counter
                    nodeCount--;
                } else {
                    // Display an error message when trying to dequeue from an empty queue
                    strcpy(errorMessage, "Error: La file est vide!");
                }
            }
            // si on a clicque Quitter
            if (CheckCollisionPointRec((Vector2){mouseX, mouseY}, (Rectangle){600, 150, 100, 40})) {
                CloseWindow();  // hna fermer la fenetre
            }
        }
        // Gestion de l'entrée utilisateur pour la valeur à insérer
        if (inputMode) {
            int key = GetKeyPressed();
            if (key >= '0' && key <= '9' && inputIndex < 3) {
                // Append digit to inputValue
                inputValue[inputIndex++] = key;
                inputValue[inputIndex] = '\0';  // Null-terminate the string
            } else if (key == KEY_ENTER) {
                // Enqueue the value and deactivate input mode
                int value = atoi(inputValue);
                enqueue(&q, value);
                inputMode = false;
                // Hide the input button after enqueuing
                showInputButton = false;
            }
        }

        BeginDrawing();
        ClearBackground((Color){0xD6, 0xCC, 0xC2, 255});
        // dessiner la file
        drawQueue(&q);
        // Dessiner "Enfiler"
        DrawRectangleRec(enfilerButton, (Color){0xF5, 0xEB, 0xE0, 255});
        DrawText("Enfiler", enfilerButton.x + 15, enfilerButton.y + 10, 20,BLACK);

        // Dessiner "Defiler"
        DrawRectangle(600, 100, 100, 40,(Color){0xF5, 0xEB, 0xE0, 255});
        DrawText("Defiler", 615, 110, 20,BLACK);

        // Dessiner "Quitter"
        DrawRectangle(600, 150, 100, 40, (Color){0xF5, 0xEB, 0xE0, 255});
        DrawText("Quitter", 615, 160, 20, BLACK);

        // Zone de l'ecriture
        if (inputMode) {
            // Afficher le bouton d'entrée à côté du bouton "Enfiler"
            DrawCircle(inputButtonCenter.x, inputButtonCenter.y, circleRadius, (Color){0xF5, 0xEB, 0xE0, 255});
            DrawText(inputValue, inputButtonCenter.x - 15, inputButtonCenter.y - 10, 20, BLACK);
        }
        // zone de message d'erreures
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
