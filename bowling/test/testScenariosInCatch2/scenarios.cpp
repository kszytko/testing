#define CATCH_CONFIG_MAIN 
#include "catch.hpp"

SCENARIO("Single frame score count") {
    GIVEN("Begining of frame") {
        WHEN("First ball knocks down less than 10 pins") {
            THEN("Frame is not over. Second ball should be played.") {
            }
        }
    }
    GIVEN("Begining of frame") {
        WHEN("First ball in frame knocks down 10 pins") {
            THEN("Frame is over. Strike achived. Score count for this frame is not counted yet") {
            }
        }
    }
    GIVEN("First ball in frame knocks down 0 pins") {
        WHEN("Second ball in frame knocks down 0 pins") {
            THEN("Frame is over. Score count for this frame is 0") {
            }
        }
    }
    GIVEN("First ball in frame knocks down 5 pins") {
        WHEN("Second ball in frame knocks down 3 pins") {
            THEN("Frame is over. Score count for this frame is 8") {
            }
        }
    }
    GIVEN("First ball in frame knocks down no more than 9 pins (0 <= knockedPins <= 9") {
        WHEN("Second ball in frame knocks down zero or other pins but one is left") {
            THEN("Frame is over. Score count for this frame is less then 10") {
            }
        }
    }
    GIVEN("First ball in frame knocks down no more than 9 pins (0 <= knockedPins <= 9") {
        WHEN("Second ball in frame knocks down all the other pins") {
            THEN("Frame is over. Spare achived. Score count for this frame is not counted yet") {
            }
        }
    }
}

SCENARIO("Two consecutive frames score count") {
    GIVEN("First ball in first frame knocks down 4 pins") {
        AND_GIVEN("Second ball in first frame knocks down 2 pins") {
            WHEN("First ball in second frame knocks down 3 pins") {
                AND_WHEN("Second ball in second frame knocks down 5 pins") {
                    THEN("Score count for first frame is 6") {
                        AND_THEN("Second frame is over. Score count for second frame is 8") {
                        }
                    }
                }
            }
        }
    }
    GIVEN("First ball in first frame knocks down all 10 pins - it is strike") {
        WHEN("First ball in second frame knocks down 3 pins") {
            AND_WHEN("Second ball in second frame knocks down 5 pins") {
                THEN("Score count for first frame is 18") {
                    AND_THEN("Second frame is over. Score count for second frame is 8") {
                    }
                }
            }
        }
    }
    GIVEN("First ball in first frame knocks down 4 pins") {
        AND_GIVEN("Second ball in first frame knocks down 6 pins - it is spare") {
            WHEN("First ball in second frame knocks down 3 pins") {
                AND_WHEN("Second ball in second frame knocks down 5 pins") {
                    THEN("Score count for first frame is 13") {
                        AND_THEN("Second frame is over. Score count for second frame is 8") {
                        }
                    }
                }
            }
        }
    }
    GIVEN("First ball in first frame knocks down 4 pins") {
        AND_GIVEN("Second ball in first frame knocks down 6 pins - it is spare") {
            WHEN("First ball in second frame knocks down all 10 pins - it is strike") {
                THEN("Score count for first frame is 20") {
                    AND_THEN("Second frame is over. Score count for second frame is not calculated yet") {
                    }
                }
            }
        }
    }
    GIVEN("First ball in first frame knocks down all 10 pins - it is strike") {
        WHEN("First ball in second frame knocks down all 10 pins - it is strike") {
            THEN("Score count for first frame is not calculated yet") {
                AND_THEN("Second frame is over. Score count for second frame is not calculated yet") {
                }
            }
        }
    }
}

SCENARIO("End of game") {
    GIVEN("Nine frames are over and counted.") {
        WHEN("First ball in last (10th) frame knocks down all 10 pins - it is strike") {
            THEN("Play two more bonus balls") {
            }
        }
    }
    GIVEN("Nine frames are over and counted.") {
        WHEN("First ball in last (10th) frame knocks down less than 10 pins ") {
            AND_WHEN("Second ball in last (10th) frame knocks down all other pins - it is spare") {
                THEN("Play one more bonus ball") {
                }
        }
    }
    GIVEN("Ten frames are over and counted. And First ball in last (10th) frame knocks down all 10 pins - it is strike") {
        WHEN("Two extra balls knock down all 10 pins each") {
            THEN("Last frame score equals 30") {
            }
        }
    }
    GIVEN("Ten frames are over and counted. And after second ball in last (10th) frame all 10 pins are knocked down - it is spare") {
        WHEN("Extra ball knocks down all 10 pins") {
            THEN("Last frame score equals 20") {
            }
        }
    }
}

SCENARIO("Whole game score count") {
    GIVEN("All 20 throws in game are missed") {
        WHEN("Final score is calculated") {
            THEN("Score equals to 0") {
            }
        }
    }
    GIVEN("All 20 throws in game knock down single pin") {
        WHEN("Final score is calculated") {
            THEN("Score equals to 20") {
            }
        }
    }
    GIVEN("All 20 throws in game knock down 5 pins each time - it means all frames are spares") {
        AND_GIVEN("Bonus ball at the end knocks down 5 pins") {
            WHEN("Final score is calculated") {
                THEN("Score equals to 150") {
                }
            }
        }
    }
    GIVEN("All 10 frames in game are strikes and two bonus balls are strikes") {
        WHEN("Final score is calculated") {
            THEN("Score equals 300") {
            }
        }
    }
    GIVEN("Strike in first frame and misses till the end") {
        WHEN("Final score is calculated") {
            THEN("Score equals 10") {
            }
        }
    }
    GIVEN("Spare in first frame and misses till the end") {
        WHEN("Final score is calculated") {
            THEN("Score equals 10") {
            }
        }
    }
}
