#ifndef EVALUATOR_EVALUATOR_HPP
#define EVALUATOR_EVALUATOR_HPP

#include <memory>

#include "../ast/node.hpp"
#include "../object/object.hpp"

std::shared_ptr<IObject> Eval(const INode &node, std::shared_ptr<Environment> env);

#endif  // EVALUATOR_EVALUATOR_HPP
