
all: main create check create2 encode

clean:
	rm -f *.o

OBJECTS = Box.o ByteSource.o StreamByteSource.o Type.o Contents.o \
          FileType.o MP4Exception.o \
          Container.o SubByteSource.o MovieHeader.o SkipContents.o \
          TrackHeader.o \
          MediaHeader.o HandlerReference.o SoundMediaHeader.o DataReference.o \
          DataEntryURL.o \
          SampleDescription.o SampleToChunk.o SampleSize.o ChunkOffset.o \
          VideoMediaHeader.o \
          SyncSample.o Meta.o TimeToSample.o EditList.o TrackExtends.o \
          MovieFragmentHeader.o \
          TrackFragmentHeader.o TrackFragmentRun.o ByteSink.o StreamByteSink.o \
          Size.o \
          EventMessage.o SegmentType.o TrackFragmentDecodeTime.o ItemList.o \
          AVCSampleEntry.o AVCConfiguration.o ParameterSet.o BitRate.o \
          InitialObjectDescriptor.o ArrayByteSource.o NALUUnescaper.o BitSource.o \
          NALU.o NALUContents.o SPS.o DashEncoder.o MovieData.o DataChunk.o \
          SampleTable.o
          
CFLAGS = -g -Wall -Werror

	
%.o: %.cc %.h 
	$(CXX) -c $< $(CFLAGS)
	
main: main.cc $(OBJECTS)
	$(CXX) -o main main.cc $(OBJECTS) $(CFLAGS)
	
create: create.cc $(OBJECTS)
	$(CXX) -o create create.cc $(OBJECTS) $(CFLAGS)
		
create2: create2.cc $(OBJECTS)
	$(CXX) -o create2 create2.cc $(OBJECTS) $(CFLAGS)
		
check: check.cc $(OBJECTS)
	$(CXX) -o check check.cc $(OBJECTS) $(CFLAGS)
	
			
encode: encode.cc $(OBJECTS)
	$(CXX) -o encode encode.cc $(OBJECTS) $(CFLAGS)
