/*
 * Copyright (c) 2020-present Daniel Trugman
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef BB_UTIL_DEFER_H
#define BB_UTIL_DEFER_H

#include <utility>

#define VAR_DEFER__(x) DEFER__ ## x
#define VAR_DEFER_(x) VAR_DEFER__(x)

// Capture all by ref
#define REF_DEFER(ops) Defer VAR_DEFER_(__COUNTER__){[&]{ ops; }}
// Capture all by val
#define VAL_DEFER(ops) Defer VAR_DEFER_(__COUNTER__){[=]{ ops; }}
// Capture nothing
#define NONE_DEFER(ops) Defer VAR_DEFER_(__COUNTER__){[ ]{ ops; }}


template<class F>
class Defer
{
public:
    explicit Defer(F&& act)
        : action(std::forward<F>(act)) {}

    Defer(const Defer&) = delete;
    Defer& operator=(const Defer&) = delete;

    Defer(Defer&&) = delete;
    Defer& operator=(Defer&&) = delete;

    ~Defer()
    {
        action();
    }

private:
    F action;
};

template<class F> Defer(F) -> Defer<F>;

#endif
