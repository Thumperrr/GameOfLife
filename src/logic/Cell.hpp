#ifndef GAMEOFLIFE_CELL_H
#define GAMEOFLIFE_CELL_H

namespace gol { namespace logic {

    class Cell
    {
        bool on, _toggle;

    public:
        Cell() : on(false), _toggle(false) {}
        Cell(bool const &state) : on(state), _toggle(false) {}
        Cell(Cell const&) = default;
        Cell(Cell &&) = default;
        Cell &operator=(Cell const&) = default;
        Cell &operator=(Cell &&) = default;
        ~Cell() = default;

        void toggle()
        {
            _toggle = true;
        }
        void update()
        {
            if(_toggle)
            {
                on = !on;
                _toggle = false;
            }
        }
        void setState(const bool &state)
        {
            on = state;
        }
        bool getState() const { return on; }
        operator bool() const { return on; }
    };

}}

#endif