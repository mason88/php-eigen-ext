<?php

echo 'testing eigen extension:<br />';

$eigen_php = new EigenPhp();

$eigen_php->random_d(5, 4);
echo('<pre>' . $eigen_php . '</pre>');

$eigen_php->constant_i(3, 3, 9);
echo('<pre>' . $eigen_php . '</pre>');

