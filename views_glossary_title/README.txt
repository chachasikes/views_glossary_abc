# $Id$

Views Glossary Title
--------------------

The module allows for fine-grained integration of the node title field with 
the Views Glossary. 

This module provides a filterable Views node title & argument field. 

Use case
--------

If you are importing nodes from a feed, under certain circumstances
the data may have punctuation & numbers preceding the alphanumeric
content of the node title.

Example:

"A" is for Apples
1. Introduction

This information might be needed to present to the user, but the
Views glossary by default would file those nodes under the first
character. Which creates a glossary that looks like this:

" 1 A B C D E ...

This module can be used to clean up the glossary sorting.
Your nodes will be listed according to the first useful letter
(of your choosing.)

A B C D E ...


Installation and Use
--------------------

1. To install, place the module in your modules folder.
Usually in sites/all/modules

2. Enable the module.

3. This module provides a default View, with the special
glossary already configured. This overrides the glossary
at the path /glossary. Glossaries can be tricky to 
configure.

You can edit the view here: admin/build/views/edit/glossary_title

4. You can also use the field in configuring your view.
* Add the Field to your view, or add an argument.
* Add filtering, either for punctuation or strings, or 
for numbers.

5. The Glossary view uses the normal Node: Title field.
This module comes with a filterable node field.

Contributors
------------
Chach Sikes (chachasikes)  IRC: chach Twitter: @chachasikes

This module was made for the Drupal Open Garden Project,
Summer 2010. 