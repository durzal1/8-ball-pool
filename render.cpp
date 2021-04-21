#include "render.h"

// draws circle
int render::drawCircle(SDL_Renderer* renderer, ball ball, int radius, bool fill)
{
    int r = ball.getColor().r;
    int g = ball.getColor().g;
    int b = ball.getColor().b;
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    int offsetx, offsety, d;
    int status;


    SDL_Point p = ball.getPixels();
    int x = p.x;
    int y = p.y;

    offsetx = 0;
    offsety = radius;
    d = radius - 1;
    status = 0;

    while (offsety >= offsetx) {
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);

        if (status < 0) {

            status = -1;
            break;
        }

        if (d >= 2 * offsetx) {
            d -= 2 * offsetx + 1;
            offsetx += 1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    if (fill) {


        offsetx = 0;
        offsety = radius;
        d = radius - 1;
        status = 0;

        while (offsety >= offsetx) {

            status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
                x + offsety, y + offsetx);
            status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
                x + offsetx, y + offsety);
            status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
                x + offsetx, y - offsety);
            status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
                x + offsety, y - offsetx);

            if (status < 0) {
                status = -1;
                break;
            }

            if (d >= 2 * offsetx) {
                d -= 2 * offsetx + 1;
                offsetx += 1;
            }
            else if (d < 2 * (radius - offsety)) {
                d += 2 * offsety - 1;
                offsety -= 1;
            }
            else {
                d += 2 * (offsety - offsetx - 1);
                offsety -= 1;
                offsetx += 1;
            }
        }
    }



    return status;

}

// draws goal
int render::drawGoal(SDL_Renderer *renderer,  goal Goal, bool fill) {

    int r = 255;
    int g = 0;
    int b = 0;
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    int offsetx, offsety, d;
    int status;

    SDL_Point p = Goal.getPixels();
    int x = p.x;
    int y = p.y;

    int radius = Goal.Radius;

    offsetx = 0;
    offsety = radius;
    d = radius - 1;
    status = 0;

    while (offsety >= offsetx) {
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);

        if (status < 0) {

            status = -1;
            break;
        }

        if (d >= 2 * offsetx) {
            d -= 2 * offsetx + 1;
            offsetx += 1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    if (fill) {


        offsetx = 0;
        offsety = radius;
        d = radius - 1;
        status = 0;

        while (offsety >= offsetx) {

            status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
                                         x + offsety, y + offsetx);
            status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
                                         x + offsetx, y + offsety);
            status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
                                         x + offsetx, y - offsety);
            status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
                                         x + offsety, y - offsetx);

            if (status < 0) {
                status = -1;
                break;
            }

            if (d >= 2 * offsetx) {
                d -= 2 * offsetx + 1;
                offsetx += 1;
            }
            else if (d < 2 * (radius - offsety)) {
                d += 2 * offsety - 1;
                offsety -= 1;
            }
            else {
                d += 2 * (offsety - offsetx - 1);
                offsety -= 1;
                offsetx += 1;
            }
        }
    }



    return status;

}
// sets the extra boundaries
// returns the points for said boundaries
std::vector<SDL_Rect> render::setBoundary(SDL_Renderer *renderer, int WIDTH, int HEIGHT, goal Goal) {
    // sets variables
    int leastx = 50, leasty = 50, mostx = int(WIDTH - Goal.Radius * 1.5), mosty = int(HEIGHT - Goal.Radius * 1.5);

    // creates the rectangles to represent the borders

    // left and right
    SDL_Rect r1{0, int(Goal.Radius * 2.8), int(Goal.Radius * 1.5), int(HEIGHT - (Goal.Radius * 5.6))};
    SDL_Rect r6{mostx, int(Goal.Radius * 2.8), int(Goal.Radius * 1.5), int(HEIGHT - (Goal.Radius * 5.6))};

    // mid left
    SDL_Rect r2{int(Goal.Radius * 2.8), 0, int(HEIGHT - (Goal.Radius * 4.4)), int(Goal.Radius * 1.5)};
    SDL_Rect r3{int(Goal.Radius * 2.8), mosty, int(HEIGHT - (Goal.Radius * 4.4)), int(Goal.Radius * 1.5)};

    // mid right
    SDL_Rect r4{WIDTH / 2 + int(Goal.Radius * 1.8) , mosty, int(HEIGHT - (Goal.Radius * 4.7)), int(Goal.Radius * 1.5)};
    SDL_Rect r5{WIDTH / 2 + int(Goal.Radius * 1.8), 0, int(HEIGHT - (Goal.Radius * 4.4)), int(Goal.Radius * 1.5)};

    // sets the render color to green
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

    // renders the rectangles
    SDL_RenderFillRect(renderer, &r1);
    SDL_RenderFillRect(renderer, &r2);
    SDL_RenderFillRect(renderer, &r3);
    SDL_RenderFillRect(renderer, &r4);
    SDL_RenderFillRect(renderer, &r5);
    SDL_RenderFillRect(renderer, &r6);

    // adds rectangles into a vector
    std::vector<SDL_Rect> rects;
    rects.push_back(r1);
    rects.push_back(r2);
    rects.push_back(r3);
    rects.push_back(r4);
    rects.push_back(r5);
    rects.push_back(r6);

    return rects;
}
// sets the secondary boundaries next to the goals
// returns the points for said boundaries
std::vector<SDL_Point> render::setBoundary2(SDL_Renderer *renderer, std::vector<goal> goals, std::vector<SDL_Rect> rects) {
    // sets each rect to a variable
    SDL_Rect r1 = rects[0];
    SDL_Rect r2 = rects[1];
    SDL_Rect r3 = rects[2];
    SDL_Rect r4 = rects[3];
    SDL_Rect r5 = rects[4];
    SDL_Rect r6 = rects[5];

    // sets the render color to red
    SDL_SetRenderDrawColor(renderer, 100, 203, 255, 255);

    /// creates the points

    // top left
    SDL_Point point1 = {r1.w, r1.y};
    SDL_Point point1_ = {r1.w / 5, r1.w};

    SDL_Point point2 = {int(goals[0].x + goals[0].Radius) ,int(goals[0].y)};
    SDL_Point point2_ = {r2.x, r2.y + int(goals[0].Radius * 1.5)};


    // bottom left
    SDL_Point point3 = {r1.w, r1.y + r1.h};
    SDL_Point point3_ = {r1.w / 10 - 10,int(goals[1].y)};

    SDL_Point point4 = {int(goals[1].x + goals[0].Radius) ,int(goals[1].y) + 7};
    SDL_Point point4_ = {r3.x, r3.y};


    // top mid
    SDL_Point point5 = {r2.w + r2.x, r2.h};
    SDL_Point point5_ = {int(goals[5].x - goals[5].Radius),int(goals[5].y)};

    SDL_Point point6 = {int(goals[5].x + goals[5].Radius) ,int(goals[5].y)};
    SDL_Point point6_ = {r5.x, r3.h};

    // bottom mid
    SDL_Point point7 = {r3.x + r3.w, r3.y};
    SDL_Point point7_ = {int(goals[4].x - goals[4].Radius),int(goals[4].y)};

    SDL_Point point8 = {int(goals[4].x + goals[4].Radius) ,int(goals[4].y)};
    SDL_Point point8_ = {r4.x, r4.y};

    // top right
    SDL_Point point9 = {r6.x, r6.y};
    SDL_Point point9_ = {int(goals[3].x + goals[3].Radius) ,int(goals[3].y)};

    SDL_Point point10 = {int(goals[3].x - goals[3].Radius) ,int(goals[3].y - 10)};
    SDL_Point point10_ = {r5.x + r5.w, r5.y + r5.h};

    // bottom right
    SDL_Point point11 = {r6.x, r6.y + r6.h};
    SDL_Point point11_ = {int(goals[2].x + goals[2].Radius) ,int(goals[2].y)};

    SDL_Point point12 = {int(goals[2].x - goals[2].Radius) ,int(goals[2].y + 10)};
    SDL_Point point12_ = {r4.x + r4.w, r4.y};

    // renders all the lines
    SDL_RenderDrawLine(renderer, point1.x, point1.y, point1_.x, point1_.y);
    SDL_RenderDrawLine(renderer, point2.x, point2.y, point2_.x, point2_.y);

    SDL_RenderDrawLine(renderer, point3.x, point3.y, point3_.x, point3_.y);
    SDL_RenderDrawLine(renderer, point4.x, point4.y, point4_.x, point4_.y);

    SDL_RenderDrawLine(renderer, point5.x, point5.y, point5_.x, point5_.y);
    SDL_RenderDrawLine(renderer, point6.x, point6.y, point6_.x, point6_.y);

    SDL_RenderDrawLine(renderer, point7.x, point7.y, point7_.x, point7_.y);
    SDL_RenderDrawLine(renderer, point8.x, point8.y, point8_.x, point8_.y);

    SDL_RenderDrawLine(renderer, point9.x, point9.y, point9_.x, point9_.y);
    SDL_RenderDrawLine(renderer, point10.x, point10.y, point10_.x, point10_.y);

    SDL_RenderDrawLine(renderer, point11.x, point11.y, point11_.x, point11_.y);
    SDL_RenderDrawLine(renderer, point12.x, point12.y, point12_.x, point12_.y);

    // adds the points to a vector
    std::vector<SDL_Point> points;
    points.push_back(point1);
    points.push_back(point1_);

    points.push_back(point2);
    points.push_back(point2_);

    points.push_back(point3);
    points.push_back(point3_);

    points.push_back(point4);
    points.push_back(point4_);

    points.push_back(point5);
    points.push_back(point5_);

    points.push_back(point6);
    points.push_back(point6_);

    points.push_back(point7);
    points.push_back(point7_);

    points.push_back(point8);
    points.push_back(point8_);

    points.push_back(point9);
    points.push_back(point9_);

    points.push_back(point10);
    points.push_back(point10_);

    points.push_back(point11);
    points.push_back(point11_);

    points.push_back(point12);
    points.push_back(point12_);

    // returns all the points
    return points;
}