#pragma once

#include <type_traits>
#include "torch/torch.h"
#include "action_space.h"
#include "type_aliases.h"
#include "constants"

template <typename T, typename... Types>
struct MatchesTypeInTupleHelper< T, std::tuple<Types...> >
{ 
    static constexpr bool value = ( std::is_same_v<T, Types> || ... );
};

template <typename T, typename Tuple>
concept MatchesTypeInTuple = MatchesTypeInTupleHelper<T, Tuple>::value;


template <typename T>
concept IsActionSpace = MatchesTypeInTuple<T, ActionSpaceTypes>;

template <typename T>
concept IsLargeActor = ( sizeof( T ) > ACTOR_STACK_ALLOC_THRESHOLD );

template <typename T>
concept IsLargeEnv = ( sizeof( T ) > ENV_STACK_ALLOC_TRHESHOLD );

template <typename T>
concept IsEnvFactory = std::is_invocable_v<T>;
