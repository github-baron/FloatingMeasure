SOURCES = /home/michae/projects/FloatingMeasure/src/Utils/Utils.cpp /home/michae/projects/FloatingMeasure/src/Measure/VectorHandle.cpp /home/michae/projects/FloatingMeasure/src/Measure/PreMeasure.cpp /home/michae/projects/FloatingMeasure/src/Measure/BaseMeasure.cpp /home/michae/projects/FloatingMeasure/src/Measure/SimpleMeasure.cpp /home/michae/projects/FloatingMeasure/src/Measure/MeasureOperator.cpp /home/michae/projects/FloatingMeasure/src/Measure/ComplexMeasure.cpp /home/michae/projects/FloatingMeasure/src/DigFloat/DigFloat.cpp /home/michae/projects/FloatingMeasure/src/FloatingMeasure/FloatingMeasure.cpp
COMMAND =@ /usr/bin/clazy-standalone -checks=level3 -p /home/michae/projects/FloatingMeasure
.PHONY: all $(SOURCES)
all: $(SOURCES)
$(SOURCES):
	@echo 'Clazy check started  for $@'
	$(COMMAND) '$@'
	@echo 'Clazy check finished for $@'
