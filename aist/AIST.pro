TEMPLATE = subdirs
SUBDIRS += MapControl \
           AistFlightRoute \
           Test

AistFlightRoute.depends = MapControl
Test.depends = MapControl

