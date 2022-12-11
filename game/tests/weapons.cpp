#include <boost/test/unit_test.hpp>
#include "KUDA/scene.h"
#include "pistol.h"
#include "shotgun.h"
#include "map.h"
#include "player.h"
#include "playerController.h"
#include "enemyController.h"
#include "enemy.h"

class TestEnemy : public Enemy
{
public:
    TestEnemy( float positionX,
               float positionY,
               float direction,
               std::unique_ptr<KUDA::PawnController>&& controller,
               int health ) : Enemy( positionX, positionY, direction, std::move( controller ), health ) {}

    std::unique_ptr<sf::Transformable> Get2DSprite() const override {
        return {};
    }

    std::unique_ptr<sf::Transformable> Get3DSprite( float lookingDirection ) const override {
        return {};
    }
};

struct SceneFixture
{
    std::shared_ptr<KUDA::Scene> scene = std::make_shared<KUDA::Scene>();
    std::shared_ptr<Player> player;

    SceneFixture() {
        scene->map = std::unique_ptr<Map>( new Map{{ 1, 1, 1, 1, 1 },
                                                   { 1, 0, 0, 0, 1 },
                                                   { 1, 0, 0, 0, 1 },
                                                   { 1, 0, 0, 0, 1 },
                                                   { 1, 1, 1, 1, 1 }} );
        std::unique_ptr<GameObjectController> controller = std::make_unique<PlayerController>( scene );
        player = std::make_shared<Player>( 25, 40, 0, std::move( controller ), 100 );
        scene->camera = std::unique_ptr<KUDA::Camera>( KUDA::Camera::FromDegrees( player, 70 ));
        scene->actors.push_back( player );
    }
};

BOOST_AUTO_TEST_SUITE( WeaponsTests )

    BOOST_AUTO_TEST_SUITE( PistolTests )

        BOOST_FIXTURE_TEST_CASE( ShootsOnlyOneTarget, SceneFixture ) {
            std::unique_ptr<GameObjectController> controller = std::make_unique<EnemyController>( scene );
            std::shared_ptr<Enemy> enemy1 = std::make_shared<TestEnemy>( 75, 38, 0, std::move( controller ), 100 );
            scene->actors.push_back( enemy1 );
            controller = std::make_unique<EnemyController>( scene );
            std::shared_ptr<Enemy> enemy2 = std::make_shared<TestEnemy>( 60, 39, 0, std::move( controller ), 100 );
            scene->actors.push_back( enemy2 );

            const_cast<std::unique_ptr<Weapon>&>(player->GetWeapons().at( "Pistol" ))->Use( *player, *scene );

            BOOST_CHECK_LT( enemy2->GetHealth(), 100 );
            BOOST_CHECK_EQUAL( enemy1->GetHealth(), 100 );
        }

        BOOST_FIXTURE_TEST_CASE( CannotShootThroughWalls, SceneFixture )
        {
            scene->map = std::unique_ptr<Map>( new Map{{ 1, 1, 1, 1, 1 },
                                                       { 1, 0, 1, 0, 1 },
                                                       { 1, 0, 1, 0, 1 },
                                                       { 1, 0, 1, 0, 1 },
                                                       { 1, 1, 1, 1, 1 }} );
            std::unique_ptr<GameObjectController> controller = std::make_unique<EnemyController>( scene );
            std::shared_ptr<Enemy> enemy1 = std::make_shared<TestEnemy>( 75, 40, 0, std::move( controller ), 100 );
            scene->actors.push_back( enemy1 );

            const_cast<std::unique_ptr<Weapon>&>(player->GetWeapons().at( "Pistol" ))->Use( *player, *scene );

            BOOST_CHECK_EQUAL( enemy1->GetHealth(), 100 );
        }

    BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_SUITE( ShotgunTests )

        BOOST_FIXTURE_TEST_CASE( CanShootMultipleTargets, SceneFixture )
        {
            std::unique_ptr<GameObjectController> controller = std::make_unique<EnemyController>( scene );
            std::shared_ptr<Enemy> enemy1 = std::make_shared<TestEnemy>( 75, 38, 0, std::move( controller ), 100 );
            scene->actors.push_back( enemy1 );
            controller = std::make_unique<EnemyController>( scene );
            std::shared_ptr<Enemy> enemy2 = std::make_shared<TestEnemy>( 75, 42, 0, std::move( controller ), 100 );
            scene->actors.push_back( enemy2 );

            BOOST_CHECK_LT( enemy1->GetHealth(), 100 );
            BOOST_CHECK_LT( enemy2->GetHealth(), 100 );
        }

        BOOST_FIXTURE_TEST_CASE( CannotShootThroughWalls, SceneFixture )
        {
            scene->map = std::unique_ptr<Map>( new Map{{ 1, 1, 1, 1, 1 },
                                                       { 1, 0, 0, 0, 1 },
                                                       { 1, 0, 1, 0, 1 },
                                                       { 1, 0, 1, 0, 1 },
                                                       { 1, 1, 1, 1, 1 }} );
            std::unique_ptr<GameObjectController> controller = std::make_unique<EnemyController>( scene );
            std::shared_ptr<Enemy> enemy1 = std::make_shared<TestEnemy>( 75, 38, 0, std::move( controller ), 100 );
            scene->actors.push_back( enemy1 );
            controller = std::make_unique<EnemyController>( scene );
            std::shared_ptr<Enemy> enemy2 = std::make_shared<TestEnemy>( 75, 42, 0, std::move( controller ), 100 );
            scene->actors.push_back( enemy2 );

            const_cast<std::unique_ptr<Weapon>&>(player->GetWeapons().at( "Shothun" ))->Use( *player, *scene );

            BOOST_CHECK_LT( enemy2->GetHealth(), 100 );
            BOOST_CHECK_EQUAL( enemy1->GetHealth(), 100 );
        }

    BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
