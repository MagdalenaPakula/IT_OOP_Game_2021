project(Game)

set(SOURCE_FILES
        src/game.cpp
        src/map.cpp
        src/gameObject.cpp
        src/gameObjectController.cpp
        src/player.cpp
        src/weapon.cpp
        src/enemy.cpp
        src/pistol.cpp
        src/shotgun.cpp
        src/pickup.cpp
        src/playerController.cpp
        src/enemyController.cpp
        src/pickupController.cpp
        src/projectileController.cpp
        src/pickUpWeaponAction.cpp
        src/pickUpAmmoAction.cpp
        src/healAction.cpp
        src/damageAction.cpp
	)

include_directories(include)

add_executable(${PROJECT_NAME} src/main.cpp ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} KUDA)

add_executable(TestGame tests/TestGame.cpp ${SOURCE_FILES})

target_link_libraries(TestGame KUDA)

enable_testing()

find_package(Boost 1.64.0 COMPONENTS "unit_test_framework" REQUIRED)

include_directories(${Boost_INCLUDE_DIR} include)

set(TEST_FILES
        tests/TestSettings.cpp
        tests/player.cpp
        tests/weapons.cpp)

add_executable(Unit_Tests
			   ${SOURCE_FILES}
			   ${TEST_FILES})

target_link_libraries(Unit_Tests ${Boost_LIBRARIES})

target_link_libraries(Unit_Tests KUDA)