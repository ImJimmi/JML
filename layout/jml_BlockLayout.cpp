#include "jml_BlockLayout.h"

//======================================================================================================================
namespace jml
{
    //==================================================================================================================
    void BlockLayout::build(ComponentLayoutSpecification* layout)
    {
        for (int i = 0; i < layout->properties.getNumProperties(); i++)
        {
            const auto name =  layout->properties.getPropertyName(i).toString();
            const auto value = layout->properties.getProperty(Identifier(name)).toString();

            if (name == "margin")
                layout->margin = getBorderSizeFromAttribute(value, layout);
            else if (name == "padding")
                layout->padding = getBorderSizeFromAttribute(value, layout);
            else
            {
                if (name == "x")
                {
                    layout->bounds.setX(getPixelValueFromAttribute(value, layout));
                    layout->autoLeft = false;
                }
                else if (name == "y")
                {
                    layout->bounds.setY(getPixelValueFromAttribute(value, layout, false));
                    layout->autoTop = false;
                }
                else if (name == "width")
                {
                    layout->bounds.setWidth(getPixelValueFromAttribute(value, layout));
                    layout->autoWidth = false;
                }
                else if (name == "height")
                {
                    layout->bounds.setHeight(getPixelValueFromAttribute(value, layout, false));
                    layout->autoHeight = false;
                }

                else if (name == "min-x")
                    layout->minBounds.setX(getPixelValueFromAttribute(value, layout));
                else if (name == "min-y")
                    layout->minBounds.setY(getPixelValueFromAttribute(value, layout, false));
                else if (name == "min-width")
                    layout->minBounds.setWidth(getPixelValueFromAttribute(value, layout));
                else if (name == "min-height")
                    layout->minBounds.setHeight(getPixelValueFromAttribute(value, layout, false));

                else if (name == "max-x")
                    layout->maxBounds.setX(getPixelValueFromAttribute(value, layout));
                else if (name == "max-y")
                    layout->maxBounds.setY(getPixelValueFromAttribute(value, layout, false));
                else if (name == "max-width")
                    layout->maxBounds.setWidth(getPixelValueFromAttribute(value, layout));
                else if (name == "max-height")
                    layout->maxBounds.setHeight(getPixelValueFromAttribute(value, layout, false));

                else if (name == "flow")
                {
                    if (value == "column")
                        layout->flow = ComponentLayoutSpecification::Flow::Column;
                    else if (value == "row")
                        layout->flow = ComponentLayoutSpecification::Flow::Row;
                }
            }
        }
    }

    void BlockLayout::perform(ComponentLayoutSpecification* layout)
    {
        if (layout->parent)
        {
            auto container = layout->parent->padding.subtractedFrom(layout->parent->component->getBounds());

            // apply parent padding to this component's bounds
            layout->bounds.translate(container.getX(), container.getY());

            if (auto prevSibling = layout->indexAmongSiblings > 0 ? &layout->parent->children[layout->indexAmongSiblings - 1] : nullptr)
            {
                if (layout->autoTop && layout->parent->flow == jml::ComponentLayoutSpecification::Flow::Column)
                    layout->bounds.setY(prevSibling->component->getBottom() + prevSibling->margin.getBottom());
                else if (layout->autoLeft && layout->parent->flow == jml::ComponentLayoutSpecification::Flow::Row)
                    layout->bounds.setX(prevSibling->component->getRight() + prevSibling->margin.getLeft());
            }

            // apply margin
            layout->bounds.translate(layout->margin.getLeft(), layout->margin.getTop());

            if (layout->autoWidth)
            {
                if (layout->parent->flow == jml::ComponentLayoutSpecification::Flow::Column)
                    layout->bounds.setRight(container.getRight());
                else
                    layout->bounds.setWidth(60);

                layout->bounds.setRight(std::min(layout->bounds.getRight(), container.getRight() - layout->margin.getRight()));
            }

            if (layout->autoHeight)
            {
                if (layout->parent->flow == jml::ComponentLayoutSpecification::Flow::Row)
                    layout->bounds.setBottom(container.getBottom());
                else
                    layout->bounds.setHeight(30);

                layout->bounds.setBottom(std::min(layout->bounds.getBottom(), container.getBottom() - layout->margin.getBottom()));
            }

            if (layout->autoMarginLeft)
            {
                auto rowExcess = container.getWidth() - layout->bounds.getWidth();
                layout->bounds.setX(container.getX() + rowExcess / 2);
            }
        }
        else
        {
            if (layout->autoWidth)
                layout->bounds.setWidth(layout->component->getWidth());

            if (layout->autoHeight)
                layout->bounds.setHeight(layout->component->getHeight());
        }

        // set the bounds
        layout->component->setBounds(layout->bounds);
    }

    //==================================================================================================================
    BorderSize<int> BlockLayout::getBorderSizeFromAttribute(const String& value,
                                                            ComponentLayoutSpecification* layout)
    {
        auto tokens = StringArray::fromTokens(value, false);

        if (tokens.size() == 1)
        {
            if (tokens[0] == "auto")
                layout->autoMarginLeft = true;

            return BorderSize<int>(
                jml::getPixelValueFromAttribute(tokens[0], layout, false),   // top
                jml::getPixelValueFromAttribute(tokens[0], layout),          // left
                jml::getPixelValueFromAttribute(tokens[0], layout, false),   // bottom
                jml::getPixelValueFromAttribute(tokens[0], layout)           // right
            );
        }
        else if (tokens.size() == 2)
        {
            if (tokens[1] == "auto")
                layout->autoMarginLeft == true;

            return BorderSize<int>(
                jml::getPixelValueFromAttribute(tokens[0], layout, false),
                jml::getPixelValueFromAttribute(tokens[1], layout),
                jml::getPixelValueFromAttribute(tokens[0], layout, false),
                jml::getPixelValueFromAttribute(tokens[1], layout)
            );
        }
        else if (tokens.size() == 3)
        {
            if (tokens[1] == "auto")
                layout->autoMarginLeft = true;

            return BorderSize<int>(
                jml::getPixelValueFromAttribute(tokens[0], layout, false),
                jml::getPixelValueFromAttribute(tokens[1], layout),
                jml::getPixelValueFromAttribute(tokens[2], layout, false),
                jml::getPixelValueFromAttribute(tokens[1], layout)
            );
        }
        else if (tokens.size() == 4)
        {
            if (tokens[3] == "auto")
                layout->autoMarginLeft = true;

            return BorderSize<int>(
                jml::getPixelValueFromAttribute(tokens[0], layout, false),
                jml::getPixelValueFromAttribute(tokens[3], layout),
                jml::getPixelValueFromAttribute(tokens[2], layout, false),
                jml::getPixelValueFromAttribute(tokens[1], layout)
            );
        }
        else
        {
            jassertfalse;
        }
    }
}   // namespace jml
