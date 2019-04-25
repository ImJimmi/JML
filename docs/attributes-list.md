# JML - Attributes List
## Components
This table lists the defined attributes that can be used for positioning individual components. Within a JML file they should be used as such:

```xml
<nameOfComponent attribute="value">
```

Attribute Name | Description | Accepted Values | Example Usage
---|---|---|---
`x` | The component's x position. | Any integer.<br>A percentage. | `x="10"`<br>`x="25%"`
`y` | The component's y position. | Any integer.<br>A percentage. | `y="5"`<br>`y="10%"`
`width` | The component's width. | Positive integers.<br>A percentage. | `width="200"`<br>`width="100%"`
`height` | The component's height. | Positive integers.<br>A percentage. | `height="50"`<br>`height="10%"`
`min-x` | The component's minimum x position. | Any integer.<br>A percentage. | `min-x="10"`<br>`min-x="25%"`
`min-y` | The component's minimum y position. | Any integer.<br>A percentage. | `min-y="5"`<br>`min-y="10%"`
`min-width` | The component's minimum width. | Positive integers.<br>A percentage. | `min-width="200"`<br>`min-width="100%"`
`min-height` | The component's minimum height. | Positive integers.<br>A percentage. | `min-height="50"`<br>`min-height="10%"`
`max-x` | The component's maximum x position. | Any integer.<br>A percentage. | `max-x="10"`<br>`max-x="25%"`
`max-y` | The component's maximum y position. | Any integer.<br>A percentage. | `max-y="5"`<br>`max-y="10%"`
`max-width` | The component's maximum width. | Positive integers.<br>A percentage. | `max-width="200"`<br>`max-width="100%"`
`max-height` | The component's maximum height. | Positive integers.<br>A percentage. | `max-height="50"`<br>`max-height="10%"`
`margin` | The gap, in pixels, around this component.<br>Removes the margin from the given size (so a component with width 100 and margin 10 will be drawn as 80 pixels wide | Positive integers.<br>Single value sets all margins.<br>Two values set the x and y margins.<br>Four values set the top, right, bottom, and left margins respectively. | `margin="10"`<br>`margin="10 20"`<br>`margin="10 20 50 20"`

## Grid
### Grid
This table lists the defined attributes that can be used with the `<grid>` tag. The `<grid>` tag should be added as a child to the component that will display as a grid, e.g.:

```xml
<componentWithGrid>
  <grid attribute="value">
    <componentInAGridCell/>
  </grid>
</componentWithGrid>
```

Attribute Name | Description | Accepted Values | Example Usage
---|---|---|---
`gap` | The gap between cells | Positive integers. | `gap="10"`
`justify-items` | The alignment of content inside the items along the rows. | "start", "end", "center", or "stretch". | `justify-items="center"`
`align-items` | The alignment of content inside the items along the columns. | "start", "end", "center", or "stretch". | `align-items="end`
`justify-content` | The alignment of items along the rows. | "start", "end", "center", "stretch", "spaceAround", "spaceBetween", or "spaceEvenly". | `justify-content="spaceAround"`
`align-content` | The alignment of items along the columns. | "start", "end", "center", "stretch", "spaceAround", "spaceBetween", or "spaceEvenly". | `align-content="spaceBetween"`
`auto-flow` | How the auto-placement algorithm places items. | "row", "column", "row-dense", or "column-dense". | `auto-flow="row"`
`columns` | The number of the columns the grid should have. | Positive integers. | `columns="3"`
`rows` | The number of rows the grid should have. | Positive integers. | `rows="5"`
`column-gap` | The gap between columns. | Positive integers. | `column-gap="15"`
`row-gap` | The gap between rows. | Positive integers. | `row-gap="20"`
`template-rows` | The set of rows the grid should have. | A space-separated list of values.<br>Each value should either be a positive integer or a fractional value ending in "fr". | `template-rows="100 1fr 3fr"`
`template-columns` | The set of columns the grid should have. | A space-separated list of values.<br>Each value should either be a positive integer or a fractional value ending in "fr". | `template-columns="50 1fr 1fr 200"`
`template-areas` | The names for each of the cells in the grid. | A space-separated list of quoted, space-separated lists.<br> use "." for an empty/unnamed cell. | `template-areas="'heading heading' 'left right'"`
`auto-columns` | The track to use for the auto dimension. | Positive integers or a fractional value ending in "fr". | `auto-columns="100"`<br>`auto-columns="1fr"`
`auto-rows` | The track to use for the auto dimension. | Positive integers or a fractional value ending in "fr". | `auto-rows="100"`<br>`auto-rows="1fr"`
`margin` | The amount of space to leave around the grid. | 1, 2, or 4 Positive integers. | `margin="10"`<br>`margin="20 30"`<br>`margin="10 20 30 20"`

### Grid Items

This table lists the defined attributes that can be used with items *within* the `<grid>` tag.

Attribute Name | Description | Accepted Values | Example Usage
---|---|---|---
`area` | The area on the grid this item should be placed in. | The name of an area defined in the grid.<br>2 or 4 positive integers to define the start (and end, if 4 values provided) of the row and column this item should be placed in. | `area="heading"`<br>`area="1 3"`<br>`area="1 1 3 4"`
`order` | The z-order for this item. | Positive integers.
`justify-self` | Where this item should be placed along the row. | "start", "end", "center", or "stretch". | `justify-self="center"`
`align-self` | Where this item should be places along the column. | "start", "end", "center", or "stretch". | `align-self="stretch"`
`column` | The column in which this item should be placed. | Positive integers, greater than 0 (1-indexed). | `column="3"`
`row` | The row in which this item should be placed. | Positive integers, greater than 0 (1-indexed). | `row="2"`
`width` | The width of the item. | Positive decimal numbers. | `width="100"`
`min-width` | The minimum width of the item. | Positive decimal numbers. | `min-width="20"`
`max-width` | The maximum width of the item. | Positive decimal number. | `max-width="200"`
`height` | The height of the item. | Positive decimal numbers. | `height="50"`
`min-height` | The minimum height of the item. | Positive decimal numbers. | `min-hight="25"`
`max-height` | The maximum height of the item. | Positive decimal number. | `max-height="100"`
`margin` | The amount of space to leave around this item. | 1, 2, or 4 positive decimal numbers. | `margin="10"`<br>`margin="10, 20"`<br>`margin="20 10 40 10"`
