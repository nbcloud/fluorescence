
#include "emitter.hpp"

#include <algorithm>

namespace fluo {
namespace ui {
namespace particles {


Emitter::Emitter(const CL_Vec3f& startPos, const CL_Vec3f& velStart, const CL_Vec3f& velEnd, float creationTime, float expireTime, unsigned int maxCount,
        float emitPerSec, bool emittedMoveWithEmitter) :
    Emittable(startPos, velStart, velEnd, creationTime, expireTime),
    emittedMaxCount_(maxCount),
    emitPerSecond_(emitPerSec),
    position_(startPosition_),
    age_(0),
    emittedFractionStore_(0.99999f), // to emit at least one child at the start
    emittedMoveWithEmitter_(emittedMoveWithEmitter)
    {

}

void Emitter::reset(const CL_Vec3f& startPos, const CL_Vec3f& velStart, const CL_Vec3f& velEnd, float creationTime, float expireTime, unsigned int maxCount,
        float emitPerSec, bool emittedMoveWithEmitter) {

    Emittable::reset(startPos, velStart, velEnd, creationTime, expireTime);
    emittedMaxCount_ = maxCount;
    emitPerSecond_ = emitPerSec;
    position_ = startPosition_;
    emittedMoveWithEmitter = emittedMoveWithEmitter;
    age_ = 0;
    emittedFractionStore_ = 0.99999f; // to emit at least one child at the start
}

void Emitter::update(float elapsedSeconds) {
    //float elapsedSeconds = ((float)elapsedMillis / 1000.f);

    // update own properties
    age_ += elapsedSeconds;
    float expireAge = (lifetimes_[1u] - lifetimes_[0u]);
    float normalizedAge = age_ / expireAge;
    CL_Vec3f positionDelta = velocityStart_ * normalizedAge +
            (velocityEnd_ - velocityStart_) * normalizedAge * normalizedAge / 2.0;
    position_ = startPosition_ + positionDelta * expireAge;


    float newCountF  = elapsedSeconds * emitPerSecond_ + emittedFractionStore_;
    unsigned int newCount = newCountF;

    if (newCount > 0) {
        updateSet(newCount, elapsedSeconds);
    }

    emittedFractionStore_ = newCountF - newCount;
}

}
}
}