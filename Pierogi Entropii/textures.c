#include <stdlib.h>

#include "textures.h"

Texture2D *LoadPlayer(void) {
    Texture2D *result = malloc(sizeof(Texture) * 4);

    result[0] = LoadTexture("resources/Player/GraczFront.png");
    result[1] = LoadTexture("resources/Player/GraczRight.png");
    result[2] = LoadTexture("resources/Player/GraczBack.png");
    result[3] = LoadTexture("resources/Player/GraczLeft.png");

    return result;
}

Texture2D *LoadFloor(void) {
    Texture2D *result = malloc(sizeof(Texture2D) * 20);

    result[0] = LoadTexture("resources/Fundamenty/floor.png");
    result[1] = LoadTexture("resources/Fundamenty/upperWall.png");
    result[2] = LoadTexture("resources/Fundamenty/lowerWall.png");
    result[3] = LoadTexture("resources/Fundamenty/leftWall.png");
    result[4] = LoadTexture("resources/Fundamenty/rightWall.png");
    result[5] = LoadTexture("resources/Fundamenty/leftUpperWall.png");
    result[6] = LoadTexture("resources/Fundamenty/rightUpperWall.png");
    result[7] = LoadTexture("resources/Fundamenty/leftLowerWall.png");
    result[8] = LoadTexture("resources/Fundamenty/rightLowerWall.png");
    result[9] = LoadTexture("resources/Fundamenty/DrzwiPrawe.png");
    result[10] = LoadTexture("resources/Fundamenty/DrzwiDolne.png");
    result[11] = LoadTexture("resources/Fundamenty/DrzwiLewe.png");
    result[12] = LoadTexture("resources/Fundamenty/DrzwiGorne.png");
    result[13] = LoadTexture("resources/Fundamenty/OknoDolne.png");
    result[14] = LoadTexture("resources/Fundamenty/OknoGora.png");
    result[15] = LoadTexture("resources/Fundamenty/PodlogaHolDark.png");
    result[16] = LoadTexture("resources/Fundamenty/PodlogaHolJasne.png");
    result[17] = LoadTexture("resources/Fundamenty/poreczgora.png");
    result[18] = LoadTexture("resources/Fundamenty/schodygora.png");
    result[19] = LoadTexture("resources/Fundamenty/poreczgoraprawo.png");

    return result;
}

Texture2D *LoadProps(void) {
    Texture2D *result = malloc(sizeof(Texture2D) * 23);

    result[0] = LoadTexture("resources/Props/table.png");
    result[1] = LoadTexture("resources/Props/chair.png");
    result[2] = LoadTexture("resources/Props/shelf.png");
    result[3] = LoadTexture("resources/Props/plant1.png");
    result[4] = LoadTexture("resources/Props/plant2.png");
    result[5] = LoadTexture("resources/Props/bed1.png");
    result[6] = LoadTexture("resources/Props/bed2.png");
    result[7] = LoadTexture("resources/Props/chairleft.png");
    result[8] = LoadTexture("resources/Props/chairright.png");
    result[9] = LoadTexture("resources/Props/czajnik.png");
    result[10] = LoadTexture("resources/Props/fotel.png");
    result[11] = LoadTexture("resources/Props/kosz1.png");
    result[12] = LoadTexture("resources/Props/kosz2.png");
    result[13] = LoadTexture("resources/Props/kosz3.png");
    result[14] = LoadTexture("resources/Props/krzesloleft.png");
    result[15] = LoadTexture("resources/Props/maszynajedzenie.png");
    result[16] = LoadTexture("resources/Props/monitorprzod.png");
    result[17] = LoadTexture("resources/Props/sofabok1.png");
    result[18] = LoadTexture("resources/Props/sofabok2.png");
    result[19] = LoadTexture("resources/Props/stolikgsa.png");
    result[20] = LoadTexture("resources/Props/stolmonitor.png");
    result[21] = LoadTexture("resources/Props/stolmonitor2.png");
    result[22] = LoadTexture("resources/Props/stolowkastol.png");

    return result;
}

Texture2D *LoadClickable(void) {
    Texture2D *result = malloc(sizeof(Texture2D) * 4);

    result[0] = LoadTexture("resources/Action/przeszukaj.png");
    result[1] = LoadTexture("resources/Action/zmienpokoj.png");
    result[2] = LoadTexture("resources/Action/use.png");
    result[3] = LoadTexture("resources/Action/DoCzajnika.png");

    return result;
}

Texture2D *LoadCollectable(void) {
    Texture2D *result = malloc(sizeof(Texture2D) * 1);

    result[0] = LoadTexture("resources/Collectables/Pierogi.png");

    return result;
}