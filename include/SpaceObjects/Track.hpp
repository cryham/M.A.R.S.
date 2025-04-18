#pragma once

#include "System/Vector2f.hpp"

#include <vector>

class Home;


class Track
{
    public:
        Track(Home* home);

        void draw() const;

    private:
        void calcTrack();
        void findAnchors();
        void addAnchor(Vector2f const& point);

        void sortAnchors();
        void sortLTR();
        void sortHalf(Vector2f const& origin, int startIndex, int endIndex, bool rightHalf, bool CW);

        void removeSharpCorners();
        void createBezier();


        std::vector<Vector2f> points_;
        std::vector<Vector2f> anchors_;
};
