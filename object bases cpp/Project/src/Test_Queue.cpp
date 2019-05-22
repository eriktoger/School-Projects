//
// Created by erik on 2019-02-28.
//

#include "catch.hpp"
#include "Queue.h"
#include "Song.h"


TEST_CASE("Test Queue"){

    Queue queue;
    Time time(0);
    Song song1;
    song1.setTitle("t1");
    song1.setArtist("a1");
    song1.setLength(time);

    Song song2;
    song2.setTitle("t2");
    song2.setArtist("a2");
    song2.setLength(time);

    Song song3;
    song3.setTitle("t3");
    song3.setArtist("a3");
    song3.setLength(time);

    Song song4;
    song4.setTitle("t4");
    song4.setArtist("a4");
    song4.setLength(time);

    Song song5;
    song5.setTitle("t5");
    song5.setArtist("a5");
    song5.setLength(time);

    Song song6;
    song6.setTitle("t6");
    song6.setArtist("a6");
    song6.setLength(time);

    Song song7;
    song7.setTitle("t7");
    song7.setArtist("a7");
    song7.setLength(time);

    queue.enque(song1);
    queue.enque(song2);
    queue.enque(song3);
    queue.enque(song4);
    queue.enque(song5);
    queue.enque(song6);
    //queue.enque(song7);
    Queue queueCopy = queue;

    REQUIRE( queue.deque() == queueCopy.deque());
    REQUIRE(queue.deque() == queueCopy.deque());
    REQUIRE(queue.deque() == queueCopy.deque());
    REQUIRE(queue.deque() == queueCopy.deque());

    // make them off sync
    queue.deque();
    REQUIRE( !(queue.deque() == queueCopy.deque()) );
    REQUIRE( !(queue.deque() == queueCopy.deque()) );

    // both queues are out of objects and returns empty once
    REQUIRE( queue.deque() == Song()  );
    REQUIRE( queueCopy.deque() == Song() );
    /*

    std::cout << queue.deque() << std::endl;
    std::cout << queue.deque() << std::endl;
    std::cout << queue.deque() << std::endl;
    std::cout << queue.deque() << std::endl;
    std::cout << queue.deque() << std::endl;
    std::cout << queue.deque() << std::endl;
    std::cout << queue.deque() << std::endl;

    std::cout << "Queue-copy" << std::endl;

    std::cout << queueCopy.deque() << std::endl;
    std::cout << queueCopy.deque() << std::endl;
    std::cout << queueCopy.deque() << std::endl;
    std::cout << queueCopy.deque() << std::endl;
    std::cout << queueCopy.deque() << std::endl;
    std::cout << queueCopy.deque() << std::endl;
    std::cout << queueCopy.deque() << std::endl;
    */

}