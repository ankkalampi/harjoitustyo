#include "BulletDynamics/Dynamics/btDynamicsWorld.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <memory>
#include <ostream>
#include <vector>
#include <string>

#include <random>

#include <omp.h>

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <sstream>
#include <btBulletDynamicsCommon.h>

constexpr int WIDTH = 1680;
constexpr int HEIGHT = 1050;


////////////////////////////////////////////////////////////----DATA----//////////////////////////////////////////////////////////////////////////////


struct Buffer {
    std::vector<float> x;
    std::vector<float> y;
};

struct LocationBuffer {
    std::vector<float> x;
    std::vector<float> y;
};

struct RectBuffer {
    std::vector<int> x;
    std::vector<int> y;
    std::vector<int> w;
    std::vector<int> h;
};

struct RenderData {
    std::vector<Uint8> r;
    std::vector<Uint8> g;
    std::vector<Uint8> b;
    std::vector<Uint8> a;
};

struct EntityData {
    std::vector<float> x;
    std::vector<float> y;
    std::vector<int> id;
    std::vector<std::string> name;
};

struct PhysicsData {

};






struct Data {



    Buffer bufferA;
    Buffer bufferB;
    RectBuffer rectBufferA;
    RectBuffer rectBufferB;


    btDynamicsWorld* world;
    std::vector<btRigidBody*> rigidBodies;

    std::vector<SDL_Vertex> vertices;
    std::vector<int> startIndices;
    std::vector<int> numVertices;
    std::vector<int> indices;

    std::vector<float> velocityX;
    std::vector<float> velocityY;

    std::vector<float> mass;

    void addRenderComponent(std::vector<SDL_Vertex> newVertices){

            size_t verticesTotal = vertices.size();
            size_t verteXCount = vertices.size();
            startIndices.push_back(verticesTotal);
            numVertices.push_back(4);
            vertices.insert(vertices.end(), newVertices.begin(), newVertices.end());
            indices.push_back(verteXCount);
            indices.push_back(verteXCount +1);
            indices.push_back(verteXCount +2);
            indices.push_back(verteXCount);
            indices.push_back(verteXCount+2);
            indices.push_back(verteXCount+3);







    }


    void createSquares(int num, int size, SDL_Color color={120, 56, 78, 255}){


        int max_value = 100; // Yläraja
        std::random_device rd; // Siemen generaattorille
        std::mt19937 gen(rd()); // Mersenne Twister -generaattori
        std::uniform_int_distribution<> xdistrib(0, WIDTH);
        std::uniform_int_distribution<> ydistrib(0, HEIGHT); // Jakautuma



        for (int i = 0; i < num; i++){
            float x = xdistrib(gen);
            float y = ydistrib(gen);

            std::vector<SDL_Vertex> verts;

            SDL_FPoint point1 = {x, y};
            SDL_FPoint point2 = {x+size, y};
            SDL_FPoint point3 = {x+size, y+size};
            SDL_FPoint point4 = {x, y+size};


            SDL_Vertex vertex1 = {point1, color, {0.0f, 0.0f}};
            SDL_Vertex vertex2 = {point2, color, {0.0f, 0.0f}};
            SDL_Vertex vertex3 = {point3, color, {0.0f, 0.0f}};
            SDL_Vertex vertex4 = {point4, color, {0.0f, 0.0f}};

            verts.push_back(vertex1);
            verts.push_back(vertex2);
            verts.push_back(vertex3);
            verts.push_back(vertex4);

            addRenderComponent(verts);




        }





    }

    void init(){


        int size = 60;
        std::vector<SDL_Color> colors;
        colors.push_back({222, 100, 79, 255});
        colors.push_back( {23, 56, 21, 255});
        colors.push_back({78, 4, 79, 255});
        colors.push_back({77, 56, 55, 255});
        colors.push_back({24, 2, 10, 255});
        colors.push_back( {17, 67, 79, 255});
        colors.push_back({100, 56, 24, 255});
        colors.push_back({180, 4, 2, 255});
        colors.push_back( {28, 56, 79, 255});
        colors.push_back( {222, 44, 11, 255});

        /*
        createSquares(1, size, color1);
        createSquares(1, size, color2);
        createSquares(1, size, color3);
        createSquares(1, size, color4);
        createSquares(1, size, color5);
        createSquares(1, size, color6);
        //createSquares(1, size, color7);
        //createSquares(1, size, color8);
        //createSquares(1, size, color9);
        //createSquares(1, size, color10);
        */
        int howMany = 2500;
        int howBig = 50;
        int rounds = 0;
        SDL_Color color;
        for (int i=0; i < howMany; ++i){

            if (rounds < colors.size()){
                color = colors[rounds];
                rounds++;
            } else {
                rounds = 0;
                color = colors[rounds];
            }
            createSquares(1, howBig, color);
        }


        }
};

struct Entity {
    int id;


    void createEntity(float x, float y){

    }
};


/////////////////////////////////////////////////////////////----RENDER SYSTEM----/////////////////////////////////////////////////////////////////////////////
enum class RenderType{
    Square,
    Triangle,
    Circle,
    Sprite
};

namespace Render{





struct RenderSystem {
    SDL_Renderer* renderer;
    SDL_Window* window;

    std::vector<SDL_Vertex>* vertices;
    std::vector<int>* startIndices;
    std::vector<int>* numVertices;
    std::vector<int>* indices;
    Data* data;

    std::vector<SDL_Vertex> test;
    bool runOnce;






    void init(Data* data){
        this->window = makeWindow();
        this->renderer = makeRenderer(this->window);
        this->data = data;
        this->vertices = &data->vertices;
        this->startIndices = &data->startIndices;
        this->numVertices = &data->numVertices;

        this->indices = &data->indices;

        this->runOnce = false;

        //makeSomeSquares();

    }

    void updateRenderDataFromPhysics(
    const std::vector<btRigidBody*>& rigidBodies,
    std::vector<SDL_Vertex>& vertices,
    const std::vector<int>& startIndices,
    const std::vector<int>& numberVertices)
        {

            /*
            std::cout << "printing startIndices: " << std::endl << "{";
            for (int val : startIndices){
                std::cout << val << ", ";
            }
            std::cout << "}" << std::endl;

            std::cout << "printing numberVertices: " << std::endl << "{";
            for (int val : numberVertices){
                std::cout << val << ", ";
            }
            std::cout << "}" << std::endl;
            */



            for (size_t entityIndex = 0; entityIndex < rigidBodies.size(); entityIndex++) {
                btRigidBody* rigidBody = rigidBodies[entityIndex];

                // Hae rigidbodyn sijainti ja orientaatio
                btTransform transform;
                transform.setIdentity();
                rigidBody->getMotionState()->getWorldTransform(transform);
                //std::cout << "entity: " << entityIndex << " ridigbody: " << rigidBodies[entityIndex] <<  std::endl;

                btVector3 position = transform.getOrigin();
                btQuaternion rotation = transform.getRotation();

                // Päivitä kaikki vertexit tähän sijaintiin ja orientaatioon
                int start = startIndices[entityIndex];
                int count = numberVertices[entityIndex];
                for (int i = 0; i < count; ++i) {
                    SDL_Vertex& vertex = vertices[start + i];

                    // Muunna vertexin sijainti rigidbodyn sijainnin ja orientaation perusteella
                    btVector3 localVertex(vertex.position.x, vertex.position.y, 0.0f);

                    /*
                    if (!runOnce) {
                        std::cout << "          entity: " << static_cast<int>(entityIndex) <<  " vertex: " << i << "  old x: " << vertex.position.x << "  old y: " << vertex.position.y   << std::endl;
                        std::cout << "entity transform: " << static_cast<int>(entityIndex) <<  " vertex: " << i << "      x: " << transform.getOrigin().x() << "      y: " << transform.getOrigin().y() << "     z: " << transform.getOrigin().y() << std::endl;
                    }

                    */

                    btVector3 worldVertex = transform * localVertex;

                    vertex.position.x = worldVertex.getX();
                    vertex.position.y = worldVertex.getY();
                    /*
                    if (vertex.position.x > WIDTH || vertex.position.x < 0 || vertex.position.y > HEIGHT || vertex.position.y < 0 ){
                        //std::cout << "entity: " << static_cast<int>(entityIndex) << " x: " << vertex.position.x << " y: " << vertex.position.y << std::endl;
                    }

                    */

                }
            }
            this->runOnce = true;
        }




    void update(){
        //SDL_Rect rec = {100, 200, 50,70};
        // haetaan pointerit vektorien alkuihin



        //makeSomething();
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 20, 90, 100, 255);
        //SDL_RenderFillRect(renderer, &rec);
        updateRenderDataFromPhysics(data->rigidBodies, data->vertices, data->startIndices, data->numVertices);
        SDL_RenderGeometry(this->renderer, NULL, this->vertices->data(), this->vertices->size(), this->indices->data(), this->indices->size());

        SDL_RenderPresent(renderer);

        //std::cout << data->rigidBodies[0] << std::endl;





    }

    void terminate(){

    }

    SDL_Window* makeWindow(){
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            throw std::runtime_error("SDL:n alustaminen epäonnistui: " + std::string(SDL_GetError()));
        }

        // luodaan ikkuna
        window = SDL_CreateWindow("SDL-testi -ikkuna",
                                                SDL_WINDOWPOS_CENTERED,
                                                SDL_WINDOWPOS_CENTERED,
                                                WIDTH, HEIGHT,
                                            SDL_WINDOW_SHOWN);

        if (!window) {
            throw std::runtime_error("SDL-ikkunan luominen epäonnistui: " + std::string(SDL_GetError()));
            SDL_Quit();
        }

        return window;
    }

    SDL_Renderer* makeRenderer(SDL_Window* window){
        // luodaan renderöijä ikkunalle
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer) {
            throw std::runtime_error("SDL-renderöijän luominen epäonnistui: " + std::string(SDL_GetError()));
            SDL_DestroyWindow(window);
            SDL_Quit();

        }

        return renderer;
    }

};

void addRenderComponent(RenderSystem rs,RenderType type, std::vector<SDL_Vertex> newVertices){
        if (type == RenderType::Square){
            size_t entityCount = rs.startIndices->size();
            size_t verteXCount = rs.vertices->size();
            rs.startIndices->push_back(entityCount);
            rs.numVertices->push_back(4);
            rs.vertices->insert(rs.vertices->end(), newVertices.begin(), newVertices.end());
            rs.indices->push_back(verteXCount);
            rs.indices->push_back(verteXCount +1);
            rs.indices->push_back(verteXCount +2);
            rs.indices->push_back(verteXCount);
            rs.indices->push_back(verteXCount+2);
            rs.indices->push_back(verteXCount+3);





        }
        else {
            std::cerr << "toiminnallisuutta ei ole lisätty vielä!" << std::endl;
        }

    }
}

//////////////////////////////////////////////////----PHYSICS SYSTEM----////////////////////////////////////////////////////////////////////////////////////////

namespace Physics{

    // bulletin törmäystarkistusryhmät
    const short COLLISION_GROUP = 0x0001;
    const short COLLISION_MASK = -1;



struct PhysicsSystem {
    btDynamicsWorld* world;
    btBroadphaseInterface* broadphase;
    btDefaultCollisionConfiguration* collisionConfig;
    btCollisionDispatcher* dispatcher;
    btSequentialImpulseConstraintSolver* solver;
    std::vector<btRigidBody*>* rigidBodies;
    Data* data;




    void init(Data* data) {
        this->data = data;
        broadphase = new btDbvtBroadphase();
        collisionConfig = new btDefaultCollisionConfiguration();
        dispatcher = new btCollisionDispatcher(collisionConfig);
        solver = new btSequentialImpulseConstraintSolver();
        world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfig);






        generateRigidBodies(world, data->vertices, data->startIndices, data->numVertices, data->rigidBodies);
    }


    void make2D(btRigidBody *rigidBody, btDynamicsWorld* world){
        btTransform zeroTranslation = btTransform::getIdentity();
        zeroTranslation.setOrigin(btVector3(0, 0, 0));  // Ei siirtoa Z-akselilla

        // Luo rajoite, joka estää liikkeen Z-akselilla
        btPoint2PointConstraint* constraint = new btPoint2PointConstraint(
            *rigidBody, btVector3(0, 0, 0));  // Rajoite X-Y-akseleilla

        world->addConstraint(constraint);
    }

    void generateRigidBodies(
        btDynamicsWorld* world,
        const std::vector<SDL_Vertex>& vertices,
        const std::vector<int>& startIndices,
        const std::vector<int>& numberVertices,
        std::vector<btRigidBody*>& rigidBodies){

            for (size_t entityIndex = 0; entityIndex < startIndices.size(); ++entityIndex){
                int start = startIndices[entityIndex];
                int count = numberVertices[entityIndex];

                // Luo törmäysmuoto (Convex Hull)
                btConvexHullShape* collisionShape = new btConvexHullShape();
                for (int i = 0; i < count; i++) {
                    const SDL_Vertex& vertex = vertices[start + i];
                    collisionShape->addPoint(btVector3(vertex.position.x, vertex.position.y, 0.0f));

                }



                std::cout << "adding shape, points in shape:  " << collisionShape->getNumPoints() << std::endl;
                // Aseta rigidbodyn alkuperäinen sijainti
                btTransform transform;
                transform.setIdentity();

                transform.setOrigin(btVector3(0.0f, 0.0f, 0.0f)); // Alkuperäinen sijainti

                // Rigidbodyn massa ja inertia
                btScalar mass = 1.0f;
                btVector3 localInertia(0, 0, 0);
                collisionShape->calculateLocalInertia(mass, localInertia);

                // Luo rigidbody
                btDefaultMotionState* motionState = new btDefaultMotionState(transform);
                btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, collisionShape, localInertia);
                btRigidBody* rigidBody = new btRigidBody(rbInfo);

                // Lisää rigidbody maailmaan
                world->addRigidBody(rigidBody, COLLISION_GROUP, COLLISION_MASK);
                make2D(rigidBody, world);
                rigidBodies.push_back(rigidBody); // Tallenna viite myöhempää päivitystä varten

            }

    }

    void update(){
        if (data == nullptr) {
    std::cerr << "data is nullptr!" << std::endl;
} else if (world == nullptr) {
    std::cerr << "data->world is nullptr!" << std::endl;
} else {
    //std::cout << "Everything looks good. Proceeding to stepSimulation." << std::endl;
}

        world->stepSimulation(1.0f / 60.0f);

    }
};
}

///////////////////////////////////////////////////----RUNTIME----///////////////////////////////////////////////////////////////////////////////////////

struct Runtime {
    Data* data;
    Render::RenderSystem renderSystem;
    Physics::PhysicsSystem physicsSystem;

    Runtime(Data* data){
        this->data = data;
    }

    void init(){
        renderSystem.init(data);
        physicsSystem.init(data);

    }

    void run(){

        // luodaan pelisilmukka
        bool quit = false;
        SDL_Event e;


        while (!quit){
            //tapahtumien käsittely
            while(SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
            }

        physicsSystem.update();
        //renderSystem.something();
        renderSystem.update();


        }

        terminate();

    }

    void terminate(){
        //Vapauta resurssit ja sulje SDL
        SDL_DestroyRenderer(renderSystem.renderer);
        SDL_DestroyWindow(renderSystem.window);
        SDL_Quit();
    }




};

////////////////////////////////////////////////////////////----APP----//////////////////////////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////----MAIN----//////////////////////////////////////////////////////////////////////////////


int main() {
    Data data;
    data.init();
    Runtime runtime(&data);

    runtime.init();
    runtime.run();



    return 0;
}
