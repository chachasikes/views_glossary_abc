Views Glossary Title
====================

The module allows for better integration of the node title field with 
the Views Glossary. 

This module provides a filterable Views node title & argument field. 

Use case
========

If you are importing nodes from a feed, under certain circumstances
the data may have punctuation & numbers preceding the alphan-numeric
content of the node title.

Example:

"A" is for Apples
1. Introduction

This information might be needed to present to the user, but the
Views glossary by default would file those nodes under the first
character. Which creates a glossary that looks like this:

" 1 A B C D E ...

So you can use this module to clean up the glossary sorting.


Installation and Use
====================

1. To install, place the module in your modules folder.
Usually in sites/all/modules

2. Enable the module.

3. This module provides a default View, with the special
glossary already configured.

4. You can also use the field in configuring your view.
* Add the Field to your view, or add an argument.
* You can check the 'filtu

Contributors
============
Chach Sikes (chachasikes)  IRC: chach Twitter: @chachasikes

This module was made for the Drupal Open Garden Project,
Summer 2010.