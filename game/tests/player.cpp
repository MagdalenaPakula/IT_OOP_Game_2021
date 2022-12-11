#include <boost/test/unit_test.hpp>

#include "player.h"
#include "pistol.h"
#include "shotgun.h"
#include "healAction.h"
#include "damageAction.h"
#include "pickUpWeaponAction.h"
#include "pickUpAmmoAction.h"
#include "playerController.h"

struct PlayerFixture
{
    std::shared_ptr<KUDA::Scene> scene = std::make_shared<KUDA::Scene>();
    Player player = Player( 0, 0, 0, std::make_unique<PlayerController>( scene ), 100 );
};

struct PlayerWithWeaponsFixture : PlayerFixture
{
    PlayerWithWeaponsFixture() {
        player.AddWeapon( std::make_unique<Pistol>());
        player.AddWeapon( std::make_unique<Shotgun>());
    }
};

BOOST_AUTO_TEST_SUITE( Player_Tests )

    BOOST_AUTO_TEST_SUITE( Damage_and_Healing )

        BOOST_FIXTURE_TEST_CASE( CannotHeal_WhenWouldExceedMaxHealth, PlayerFixture )
        {
            player.TakeDamage( 20 );
            BOOST_CHECK_EQUAL( player.GetHealth(), 80 );
            player.Heal( 10 );
            BOOST_CHECK_EQUAL( player.GetHealth(), 90 );
            player.Heal( 20 );
            BOOST_CHECK_EQUAL( player.GetHealth(), 100 );
        }

        BOOST_FIXTURE_TEST_CASE( Dies_WhenHealthBelowZero, PlayerFixture )
        {
            player.TakeDamage( 100 );
            BOOST_REQUIRE_EQUAL( player.IsAlive(), false );
        }

        BOOST_FIXTURE_TEST_CASE( CannotHeal_WhenDead, PlayerFixture )
        {
            player.TakeDamage( 100 );
            player.Heal( 50 );
            BOOST_CHECK_EQUAL( player.GetHealth(), 0 );
            BOOST_CHECK_EQUAL( player.IsAlive(), false );
        }

    BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_SUITE( Actions )

        BOOST_FIXTURE_TEST_CASE( HealActionWorks, PlayerFixture )
        {
            auto action = HealAction( 20 );
            player.TakeDamage( 40 );
            BOOST_REQUIRE_EQUAL( player.GetHealth(), 60 );
            action.InvokeOn( player );
            BOOST_CHECK_EQUAL( player.GetHealth(), 80 );
        }

        BOOST_FIXTURE_TEST_CASE( DamageActionWorks, PlayerFixture )
        {
            auto action = DamageAction( 20 );
            BOOST_REQUIRE_EQUAL( player.GetHealth(), 100 );
            action.InvokeOn( player );
            BOOST_CHECK_EQUAL( player.GetHealth(), 80 );
        }

        BOOST_FIXTURE_TEST_CASE( PickUpWeaponActionWorks, PlayerFixture )
        {
            BOOST_REQUIRE( !player.GetWeapons().contains( "Pistol" ));
            BOOST_REQUIRE( !player.GetWeapons().contains( "Shotgun" ));

            auto pickupPistol = PickUpWeaponAction( std::make_unique<Pistol>());
            auto pickupShotgun = PickUpWeaponAction( std::make_unique<Shotgun>());

            pickupPistol.InvokeOn( player );
            BOOST_CHECK_EQUAL( player.GetWeapons().at( "Pistol" )->GetType(), "Pistol" );
            BOOST_CHECK( !player.GetWeapons().contains( "Shotgun" ));

            pickupShotgun.InvokeOn( player );
            BOOST_CHECK_EQUAL( player.GetWeapons().at( "Pistol" )->GetType(), "Pistol" );
            BOOST_CHECK_EQUAL( player.GetWeapons().at( "Shotgun" )->GetType(), "Shotgun" );
        }

        BOOST_FIXTURE_TEST_CASE( PickUpAmmoActionWorks, PlayerWithWeaponsFixture )
        {
            BOOST_REQUIRE( player.GetWeapons().contains( "Pistol" ));
            BOOST_REQUIRE( player.GetWeapons().contains( "Shotgun" ));
            int pistolAmmo = player.GetWeapons().at( "Pistol" )->GetAmmo();
            int shotgunAmmo = player.GetWeapons().at( "Shotgun" )->GetAmmo();

            auto pickupPistolAmmo = PickUpAmmoAction( "Pistol", 69 );
            pickupPistolAmmo.InvokeOn( player );
            auto pickupShotgunAmmo = PickUpAmmoAction( "Shotgun", 420 );
            pickupShotgunAmmo.InvokeOn( player );

            BOOST_CHECK_EQUAL( player.GetWeapons().at( "Pistol" )->GetAmmo(), pistolAmmo + 69 );
            BOOST_CHECK_EQUAL( player.GetWeapons().at( "Shotgun" )->GetAmmo(), shotgunAmmo + 420 );
        }

    BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()