#include <TrainingStep>

class MockStep : TrainingStep<MockStep, int, std::tuple<double> { 
    MockStep( TrainingStep &next ) : next_step = next
}
    

