    this->window->setView(*this->view);

    //draw background

    //draw lines
    float x = 0.0f, y = 0.0f;

    sf::Transform transformX, transformY;
    transformX.translate(sf::Vector2f(x, 0.0f));
    transformY.translate(sf::Vector2f(0.0f, y));

    sf::Vertex horLine[] ={
        sf::Vertex(sf::Vector2f(0.0f, 0.0f)),
        sf::Vertex(sf::Vector2f(map.width, 0.0f))
    };

    horLine[0].color = sf::Color(50, 50, 50, 255);
    horLine[1].color = sf::Color(50, 50, 50, 255);

    while(y <= map.height + 1){
        this->window->draw(horLine, 2, sf::Lines, transformY);

        y += map.cellWidth;
        transformY.translate(sf::Vector2f(0.0f, map.cellWidth));
    }

    sf::Vertex verLine[] = {
        sf::Vertex(sf::Vector2f(0.0f, 0.0f)),
        sf::Vertex(sf::Vector2f(0.0f, map.height))
    };

    verLine[0].color = sf::Color(50, 50, 50, 255);
    verLine[1].color = sf::Color(50, 50, 50, 255);

    while(x <= map.width + 1){
        this->window->draw(verLine, 2, sf::Lines, transformX);
        x += map.cellWidth;
        transformX.translate(sf::Vector2f(map.cellWidth, 0.0f));
    }