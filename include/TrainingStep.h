#ifndef TRAININGSTEP_H
#define TRAININGSTEP_H

template <typename T, typename InfoType, typename NextStepType>
class TrainingStep { 
public:
    // Methods
    bool execute( InfoType &info ) { 
        int result = execute_step( info );
        return ( !( result || next_step->execute( info ) ) )

}

    ResultType execute_step( InfoType &info ) {
        return static_cast<T*>( this )->execute_step( info );
        
}
    // Setters
    void set_next( const TrainingStep &next ){ 
        next_step = &next;
}

protected:
    // Attributes
    std::unique_ptr<TrainingStep<>> next_step;
};

/*
class ComputeTargetStep : public TrainingStep<ComputeTargetStep> { 
public:
        TrainingInfo my_execute( TrainingInfo info ) { 
    // Unpack Training Info and perform fancy target computation   
}
    std::unique_ptr<TrainingStep> next_step { ComputeGradientStep }
i};
*/
#endif // TRAININGSTEP_H
